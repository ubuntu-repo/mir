/*
 * Copyright © 2014 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 3,
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by: Alexandros Frantzis <alexandros.frantzis@canonical.com>
 */

#include "mir/frontend/session_credentials.h"

#include "mir_toolkit/mir_client_library.h"
#include "mir_toolkit/mir_screencast.h"

#include "mir_test_framework/connected_client_headless_server.h"
#include "mir/test/doubles/stub_session_authorizer.h"
#include "mir/test/fake_shared.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace mtf = mir_test_framework;
namespace mtd = mir::test::doubles;
namespace mf = mir::frontend;
namespace mt = mir::test;

namespace
{
struct MockSessionAuthorizer : public mtd::StubSessionAuthorizer
{
    MOCK_METHOD1(screencast_is_allowed, bool(mf::SessionCredentials const&));
};

struct Screencast : mtf::HeadlessInProcessServer
{
    MirScreencastParameters default_screencast_params {
        {0, 0, 1, 1}, 1, 1, mir_pixel_format_abgr_8888};

    MockSessionAuthorizer mock_authorizer;

    void SetUp() override
    {
        server.override_the_session_authorizer([this]
            { return mt::fake_shared(mock_authorizer); });

        mtf::HeadlessInProcessServer::SetUp();
    }
};
}

// TODO test case(s) showing screencast works. lp:1396681

TEST_F(Screencast, with_invalid_params_fails)
{
    using namespace testing;

    EXPECT_CALL(mock_authorizer, screencast_is_allowed(_))
        .WillOnce(Return(true));

    auto const connection = mir_connect_sync(new_connection().c_str(), __PRETTY_FUNCTION__);

    MirScreencastParameters params = default_screencast_params;
    params.width = params.height = 0;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
    auto screencast = mir_connection_create_screencast_sync(connection, &params);
#pragma GCC diagnostic pop
    EXPECT_FALSE(mir_screencast_is_valid(screencast));

    mir_screencast_release_sync(screencast);

    params = default_screencast_params;
    params.region.width = params.region.height = 0;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
    screencast = mir_connection_create_screencast_sync(connection, &params);
#pragma GCC diagnostic push
    EXPECT_FALSE(mir_screencast_is_valid(screencast));

    mir_screencast_release_sync(screencast);

    params = default_screencast_params;
    params.pixel_format = mir_pixel_format_invalid;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
    screencast = mir_connection_create_screencast_sync(connection, &params);
#pragma GCC diagnostic pop
    EXPECT_FALSE(mir_screencast_is_valid(screencast));

    mir_screencast_release_sync(screencast);
    mir_connection_release(connection);
}

TEST_F(Screencast, when_unauthorized_fails)
{
    using namespace testing;

    EXPECT_CALL(mock_authorizer, screencast_is_allowed(_))
        .WillOnce(Return(false));

    auto const connection = mir_connect_sync(new_connection().c_str(), __PRETTY_FUNCTION__);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
    auto screencast = mir_connection_create_screencast_sync(connection, &default_screencast_params);
#pragma GCC diagnostic pop
    EXPECT_FALSE(mir_screencast_is_valid(screencast));

    mir_screencast_release_sync(screencast);
    mir_connection_release(connection);
}
