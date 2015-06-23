/*
 * Copyright © 2015 Canonical Ltd.
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
 * Authored By: Alan Griffiths <alan@octopull.co.uk>
 */

#include "default_window_manager.h"

#include "mir/scene/placement_strategy.h"
#include "mir/scene/session.h"
#include "mir/scene/session_coordinator.h"
#include "mir/scene/surface.h"
#include "mir/scene/surface_creation_parameters.h"
#include "mir/shell/focus_controller.h"
#include "mir/shell/surface_ready_observer.h"
#include "mir/shell/surface_specification.h"

namespace mf = mir::frontend;
namespace ms = mir::scene;
namespace msh = mir::shell;
namespace me = mir::examples;

me::DefaultWindowManager::DefaultWindowManager(
    msh::FocusController* focus_controller,
    std::shared_ptr<scene::PlacementStrategy> const& placement_strategy,
    std::shared_ptr<scene::SessionCoordinator> const& session_coordinator) :
    focus_controller{focus_controller},
    placement_strategy{placement_strategy},
    session_coordinator{session_coordinator}
{
}

void me::DefaultWindowManager::add_session(std::shared_ptr<scene::Session> const& session)
{
    focus_controller->set_focus_to(session, {});
}

void me::DefaultWindowManager::remove_session(std::shared_ptr<scene::Session> const& /*session*/)
{
    auto const next_session = session_coordinator->successor_of({});
    if (next_session)
        focus_controller->set_focus_to(next_session, next_session->default_surface());
    else
        focus_controller->set_focus_to(next_session, {});
}

auto me::DefaultWindowManager::add_surface(
    std::shared_ptr<scene::Session> const& session,
    scene::SurfaceCreationParameters const& params,
    std::function<frontend::SurfaceId(std::shared_ptr<scene::Session> const& session, scene::SurfaceCreationParameters const& params)> const& build)
-> frontend::SurfaceId
{
    auto const result = build(session, placement_strategy->place(*session, params));
    auto const surface = session->surface(result);

    surface->add_observer(std::make_shared<msh::SurfaceReadyObserver>(
        [this](std::shared_ptr<scene::Session> const& session,
               std::shared_ptr<scene::Surface> const& surface)
            {
                focus_controller->set_focus_to(session, surface);
            },
        session,
        surface));

    return result;
}

void me::DefaultWindowManager::modify_surface(
    std::shared_ptr<scene::Session> const& /*session*/,
    std::shared_ptr<scene::Surface> const& surface,
    msh::SurfaceSpecification const& modifications)
{
    if (modifications.name.is_set())
        surface->rename(modifications.name.value());
}


void me::DefaultWindowManager::remove_surface(
    std::shared_ptr<scene::Session> const& /*session*/,
    std::weak_ptr<scene::Surface> const& /*surface*/)
{
}

void me::DefaultWindowManager::add_display(geometry::Rectangle const& /*area*/)
{
}

void me::DefaultWindowManager::remove_display(geometry::Rectangle const& /*area*/)
{
}

bool me::DefaultWindowManager::handle_keyboard_event(MirKeyboardEvent const* /*event*/)
{
    return false;
}

bool me::DefaultWindowManager::handle_touch_event(MirTouchEvent const* /*event*/)
{
    return false;
}

bool me::DefaultWindowManager::handle_pointer_event(MirPointerEvent const* /*event*/)
{
    return false;
}

int me::DefaultWindowManager::set_surface_attribute(
    std::shared_ptr<scene::Session> const& /*session*/,
    std::shared_ptr<scene::Surface> const& surface,
    MirSurfaceAttrib attrib,
    int value)
{
    return surface->configure(attrib, value);
}