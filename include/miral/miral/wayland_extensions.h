/*
 * Copyright © 2018-2019 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 or 3 as
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
 * Authored by: Alan Griffiths <alan@octopull.co.uk>
 */

#ifndef MIRAL_WAYLAND_EXTENSIONS_H
#define MIRAL_WAYLAND_EXTENSIONS_H

#include "application.h"

#include <functional>
#include <memory>
#include <string>

struct wl_display;
struct wl_client;
struct wl_resource;

namespace mir { class Server; }

namespace miral
{
class Window;

/// Enable configuration of the Wayland extensions enabled at runtime.
///
/// This adds the command line option '--wayland-extensions' the corresponding
/// MIR_SERVER_WAYLAND_EXTENSIONS environment variable, and the wayland-extensions
/// config line.
///   * The server can add support for additional extensions
///   * The server can specify the configuration defaults
///   * Mir's option handling allows the defaults to be overridden
/// \remark Since MirAL 2.4
class WaylandExtensions
{
public:
    /// Default to enabling the extensions recommended by Mir
    WaylandExtensions();

    /// Initialize "enabled by default" to a custom set of extensions (colon
    /// separated list).
    /// \note This can only be a subset of supported_extensions()
    explicit WaylandExtensions(std::string const& default_value);

    void operator()(mir::Server& server) const;

    /// All Wayland extensions currently supported (colon separated list).
    /// This includes both the recommended_extensions() and any extensions that
    /// have been added using add_extension().
    /// \deprecated This is of no real use to the server, just for documenting
    /// the configuration option.
    auto supported_extensions() const -> std::string;

    /// Default for extensions to enabled recommended by Mir (colon separated list)
    /// \remark Since MirAL 2.5
    static auto recommended_extensions() -> std::string;

    ~WaylandExtensions();
    WaylandExtensions(WaylandExtensions const&);
    auto operator=(WaylandExtensions const&) -> WaylandExtensions&;

    /// Context information useful for implementing Wayland extensions
    /// \remark Since MirAL 2.5
    class Context
    {
    public:
        virtual auto display() const -> wl_display* = 0;
        virtual void run_on_wayland_mainloop(std::function<void()>&& work) const = 0;

    protected:
        Context() = default;
        virtual ~Context() = default;
        Context(Context const&) = delete;
        Context& operator=(Context const&) = delete;
    };

    /// A Builder creates and registers an extension protocol.
    /// \remark Since MirAL 2.5
    struct Builder
    {
        /// Name of the protocol extension
        std::string name;

        /// Functor that creates and registers an extension protocol
        /// \param context giving access to:
        ///   * the wl_display (so that, for example, the extension can be registered); and,
        ///   * allowing server initiated code to be executed on the Wayland mainloop.
        /// \return a shared pointer to the implementation. (Mir will manage the lifetime)
        std::function<std::shared_ptr<void>(Context const* context)> build;
    };

    /// \remark Since MirAL 2.5
    using Filter = std::function<bool(Application const& app, char const* protocol)>;

    /// Set an extension filter callback to control the extensions available to specific clients
    /// \remark Since MirAL 2.5
    void set_filter(Filter const& extension_filter);

    /// Add a bespoke Wayland extension both to "supported" and "enabled by default".
    /// \remark Since MirAL 2.5
    void add_extension(Builder const& builder);

    /// Add a bespoke Wayland extension both to "supported" but not "enabled by default".
    /// \remark Since MirAL 2.5
    void add_extension_disabled_by_default(Builder const& builder);

private:
    struct Self;
    std::shared_ptr<Self> self;
};

/// Get the MirAL application for a wl_client.
/// \return The application (null if no application is found)
/// \remark Since MirAL 2.5
auto application_for(wl_client* client) -> Application;

/// Get the MirAL application for a wl_resource.
/// \return The application (null if no application is found)
/// \remark Since MirAL 2.5
auto application_for(wl_resource* resource) -> Application;

/// Get the MirAL Window for a Wayland Surface, XdgSurface, etc.
/// Note that there may not be a corresponding miral::Window (e.g. the
/// surface is created and assigned properties before 'commit' creates the
/// miral::Window).
///
/// \return The window (null if no window is found)
/// \remark Since MirAL 2.5
auto window_for(wl_resource* surface) -> Window;
}

#endif //MIRAL_WAYLAND_EXTENSIONS_H
