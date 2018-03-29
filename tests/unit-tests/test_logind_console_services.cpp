/*
 * Copyright © 2018 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 or 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by: Christopher James Halse Rogers <christopher.halse.rogers@canonical.com>
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <gio/gio.h>
#include <cstdio>

#include "mir_test_framework/executable_path.h"
#include "mir_test_framework/process.h"
#include "mir_test_framework/temporary_environment_value.h"
#include "mir/test/pipe.h"
#include "mir/test/signal.h"

#include "src/server/console/logind_console_services.h"

namespace mtf = mir_test_framework;

namespace
{
struct DBusDaemon
{
    std::string const address;
    std::shared_ptr<mtf::Process> process;
};

DBusDaemon spawn_bus_with_config(std::string const& config_path)
{
    mir::test::Pipe child_stdout;

    auto daemon = mtf::fork_and_run_in_a_different_process(
        [&config_path, out = child_stdout.write_fd()]()
        {
            if (::dup2(out, 1) < 0)
            {
                std::cerr << "Failed to redirect child output" << std::endl;
                return;
            }

            execlp(
                "dbus-daemon",
                "dbus-daemon",
                "--print-address",
                "--config-file",
                config_path.c_str(),
                (char*)nullptr);
        },
        []()
        {
            // The only way we call the exit function is if exec() fails.
            return EXIT_FAILURE;
        });

    char buffer[1024];
    auto bytes_read = ::read(child_stdout.read_fd(), buffer, sizeof(buffer));
    if (bytes_read < 0)
    {
        BOOST_THROW_EXCEPTION((
            std::system_error{
                errno,
                std::system_category(),
                "Failed to read address from dbus-daemon"}));
    }

    if (buffer[bytes_read - 1] != '\n')
    {
        BOOST_THROW_EXCEPTION((std::runtime_error{"Failed to read all of dbus address?"}));
    }
    buffer[bytes_read - 1] = '\0';
    return DBusDaemon {
        buffer,
        daemon
    };
}

}

class LogindConsoleServices : public testing::Test
{
public:
    LogindConsoleServices()
        : system_bus{spawn_bus_with_config(mtf::test_data_path() + "/dbus/system.conf")},
          session_bus{spawn_bus_with_config(mtf::test_data_path() + "/dbus/session.conf")},
          system_bus_env{"DBUS_SYSTEM_BUS_ADDRESS", system_bus.address.c_str()},
          session_bus_env{"DBUS_SESSION_BUS_ADDRESS", session_bus.address.c_str()},
          starter_bus_type_env{"DBUS_STARTER_BUS_TYPE", "session"},
          starter_bus_env{"DBUS_STARTER_BUS_ADDRESS", session_bus.address.c_str()},
          bus_connection{
              g_bus_get_sync(
                  G_BUS_TYPE_SYSTEM,
                  nullptr,
                  nullptr),
              &g_object_unref}
    {
        if (!bus_connection)
        {
            BOOST_THROW_EXCEPTION((std::runtime_error{"Failed to connect to mock System bus"}));
        }
    }

    void add_any_active_session()
    {
        add_session(
            "42",
            "seat0",
            1000,
            "test_user",
            true,
            "");
    }

    void add_session(
        char const* id,
        char const* seat,
        uint32_t uid,
        char const* username,
        bool active,
        char const* take_control_code)
    {
        auto result = std::unique_ptr<GVariant, decltype(&g_variant_unref)>{
            g_dbus_connection_call_sync(
                bus_connection.get(),
                "org.freedesktop.login1",
                "/org/freedesktop/login1",
                "org.freedesktop.DBus.Mock",
                "AddSession",
                g_variant_new(
                    "(ssusb)",
                    id,
                    seat,
                    uid,
                    username,
                    active),
                nullptr,
                G_DBUS_CALL_FLAGS_NO_AUTO_START,
                1000,
                nullptr,
                nullptr),
            &g_variant_unref};

        if (!result)
        {
            BOOST_THROW_EXCEPTION((std::runtime_error{"Failed to add mock session"}));
        }

        // Result is a 1-tuple (session_object_path, )
        auto const session_path =
            g_variant_get_string(g_variant_get_child_value(result.get(), 0), nullptr);

        GError* error{nullptr};
        result.reset(
            g_dbus_connection_call_sync(
                bus_connection.get(),
                "org.freedesktop.login1",
                session_path,
                "org.freedesktop.DBus.Mock",
                "AddMethod",
                g_variant_new(
                    "(sssss)",
                    "org.freedesktop.login1.Session",
                    "TakeControl",
                    "b",
                    "",
                    take_control_code),
                nullptr,
                G_DBUS_CALL_FLAGS_NONE,
                1000,
                nullptr,
                &error));

        if (!result)
        {
            auto error_msg = error ? error->message : "Unknown error";
            BOOST_THROW_EXCEPTION((std::runtime_error{error_msg}));
        }
    }

    void ensure_mock_logind()
    {
        if (dbusmock)
            return;

        dbusmock = mtf::fork_and_run_in_a_different_process(
            []()
            {
                execlp(
                    "python3",
                    "python3",
                    "-m", "dbusmock",
                    "--template", "logind",
                    (char*)nullptr);
            },
            []()
            {
                return EXIT_FAILURE;
            });

        bool mock_on_bus{false};
        auto const watch_id = g_bus_watch_name(
            G_BUS_TYPE_SYSTEM,
            "org.freedesktop.login1",
            G_BUS_NAME_WATCHER_FLAGS_NONE,
            [](auto, auto, auto, gpointer ctx)
            {
                *static_cast<bool*>(ctx) = true;
            },
            [](auto, auto, auto)
            {
            },
            &mock_on_bus,
            nullptr);

        while (!mock_on_bus)
        {
            g_main_context_iteration(g_main_context_default(), true);
        }

        g_bus_unwatch_name(watch_id);
    }

private:
    DBusDaemon const system_bus;
    DBusDaemon const session_bus;
    mtf::TemporaryEnvironmentValue system_bus_env;
    mtf::TemporaryEnvironmentValue session_bus_env;
    mtf::TemporaryEnvironmentValue starter_bus_type_env;
    mtf::TemporaryEnvironmentValue starter_bus_env;
    std::unique_ptr<GDBusConnection, decltype(&g_object_unref)> bus_connection;
    std::shared_ptr<mtf::Process> dbusmock;
};

TEST_F(LogindConsoleServices, happy_path_succeeds)
{
    ensure_mock_logind();
    add_any_active_session();

    mir::LogindConsoleServices test{};
}

TEST_F(LogindConsoleServices, construction_fails_if_cannot_claim_control)
{
    ensure_mock_logind();

    add_session(
        "S3",
        "seat0",
        1001,
        "testy",
        true,
        "raise dbus.exceptions.DBusException('Device or resource busy (36)', name='System.Error.EBUSY')");

    EXPECT_THROW(
        mir::LogindConsoleServices test{};,
        std::runtime_error);
}
