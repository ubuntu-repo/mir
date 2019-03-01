/*
 * Copyright © 2018 Canonical Ltd.
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
 * Authored by: Christopher James Halse Rogers <christopher.halse.rogers@canonical.com>
 */

#include "wl_pointer.h"

#include "wayland_utils.h"
#include "wl_surface.h"

#include "mir/executor.h"
#include "mir/client/event.h"
#include "mir/frontend/session.h"
#include "mir/frontend/surface.h"
#include "mir/frontend/buffer_stream.h"
#include "mir/geometry/displacement.h"

#include <linux/input-event-codes.h>

namespace mf = mir::frontend;
using namespace mir::geometry;

struct mf::WlPointer::Cursor
{
    virtual void apply_to(WlSurface* surface) = 0;
    virtual ~Cursor() = default;
    Cursor() = default;

    Cursor(Cursor const&) = delete;
    Cursor& operator=(Cursor const&) = delete;
};

namespace
{
struct NullCursor : mf::WlPointer::Cursor
{
    void apply_to(mf::WlSurface*) override {}
};
}

mf::WlPointer::WlPointer(
    wl_client* client,
    wl_resource* parent,
    uint32_t id,
    std::function<void(WlPointer*)> const& on_destroy)
    : Pointer(client, parent, id),
      display{wl_client_get_display(client)},
      on_destroy{on_destroy},
      cursor{std::make_unique<NullCursor>()}
{
}

mf::WlPointer::~WlPointer()
{
    if (focused_surface)
        focused_surface.value()->remove_destroy_listener(this);
    on_destroy(this);
}

void mf::WlPointer::handle_event(MirPointerEvent const* event, WlSurface* surface)
{
    switch(mir_pointer_event_action(event))
    {
        case mir_pointer_action_button_down:
        case mir_pointer_action_button_up:
        {
            auto const current_pointer_buttons  = mir_pointer_event_buttons(event);
            auto const timestamp = mir_input_event_get_event_time_ms(mir_pointer_event_input_event(event));

            for (auto const& mapping :
                {
                    std::make_pair(mir_pointer_button_primary, BTN_LEFT),
                    std::make_pair(mir_pointer_button_secondary, BTN_RIGHT),
                    std::make_pair(mir_pointer_button_tertiary, BTN_MIDDLE),
                    std::make_pair(mir_pointer_button_back, BTN_BACK),
                    std::make_pair(mir_pointer_button_forward, BTN_FORWARD),
                    std::make_pair(mir_pointer_button_side, BTN_SIDE),
                    std::make_pair(mir_pointer_button_task, BTN_TASK),
                    std::make_pair(mir_pointer_button_extra, BTN_EXTRA)
                })
            {
                if (mapping.first & (current_pointer_buttons ^ last_buttons))
                {
                    auto const state = (mapping.first & current_pointer_buttons) ?
                        ButtonState::pressed :
                        ButtonState::released;

                    auto const serial = wl_display_next_serial(display);
                    send_button_event(serial, timestamp, mapping.second, state);
                    handle_frame();
                }
            }

            last_buttons = current_pointer_buttons;
            break;
        }
        case mir_pointer_action_enter:
        {
            auto point = Point{
                mir_pointer_event_axis_value(event, mir_pointer_axis_x),
                mir_pointer_event_axis_value(event, mir_pointer_axis_y)};
            auto transformed = surface->transform_point(point);
            handle_enter(transformed.position, transformed.surface);
            handle_frame();
            break;
        }
        case mir_pointer_action_leave:
        {
            handle_leave();
            handle_frame();
            break;
        }
        case mir_pointer_action_motion:
        {
            // TODO: properly group vscroll and hscroll events in the same frame (as described by the frame
            //  event description in wayland.xml) and send axis_source, axis_stop and axis_discrete events where
            //  appropriate (may require significant reworking of the input system)

            bool needs_frame = false;
            auto const timestamp = mir_input_event_get_event_time_ms(mir_pointer_event_input_event(event));
            auto point = Point{
                mir_pointer_event_axis_value(event, mir_pointer_axis_x),
                mir_pointer_event_axis_value(event, mir_pointer_axis_y)};
            auto transformed = surface->transform_point(point);

            if (focused_surface && transformed.surface == focused_surface.value())
            {
                if (!last_position || transformed.position != last_position.value())
                {
                    send_motion_event(
                        timestamp,
                        transformed.position.x.as_int(),
                        transformed.position.y.as_int());
                    last_position = transformed.position;
                    needs_frame = true;
                }
            }
            else
            {
                if (focused_surface)
                    handle_leave();
                handle_enter(transformed.position, transformed.surface);
                needs_frame = true;
            }

            auto hscroll = mir_pointer_event_axis_value(event, mir_pointer_axis_hscroll) * 10;
            if (hscroll != 0)
            {
                send_axis_event(timestamp,
                                Axis::horizontal_scroll,
                                hscroll);
                needs_frame = true;
            }

            auto vscroll = mir_pointer_event_axis_value(event, mir_pointer_axis_vscroll) * 10;
            if (vscroll != 0)
            {
                send_axis_event(timestamp,
                                Axis::vertical_scroll,
                                vscroll);
                needs_frame = true;
            }

            if (needs_frame)
            {
                handle_frame();
            }
            break;
        }
        case mir_pointer_actions:
            break;
    }
}

void mf::WlPointer::handle_enter(Point position, WlSurface* surface)
{
    cursor->apply_to(surface);
    auto const serial = wl_display_next_serial(display);
    send_enter_event(
        serial,
        surface->raw_resource(),
        position.x.as_int(),
        position.y.as_int());
    surface->add_destroy_listener(
        this,
        [this]()
        {
            handle_leave();
        });
    focused_surface = surface;
}

void mf::WlPointer::handle_leave()
{
    if (!focused_surface)
        return;
    focused_surface.value()->remove_destroy_listener(this);
    auto const serial = wl_display_next_serial(display);
    send_leave_event(
        serial,
        focused_surface.value()->raw_resource());
    focused_surface = std::experimental::nullopt;
    last_position = std::experimental::nullopt;
}

void mf::WlPointer::handle_frame()
{
    if (version_supports_frame())
        send_frame_event();
}

namespace
{
struct WlStreamCursor : mf::WlPointer::Cursor
{
    WlStreamCursor(
        std::shared_ptr<mf::Session> const session,
        std::shared_ptr<mf::BufferStream> const& stream,
        Displacement hotspot);

    void apply_to(mf::WlSurface* surface) override;

    std::shared_ptr<mf::Session> const session;
    std::shared_ptr<mf::BufferStream> const stream;
    Displacement const hotspot;
};

struct WlHiddenCursor : mf::WlPointer::Cursor
{
    WlHiddenCursor(std::shared_ptr<mf::Session> const session);
    void apply_to(mf::WlSurface* surface) override;

    std::shared_ptr<mf::Session> const session;
};
}

void mf::WlPointer::set_cursor(
    uint32_t serial,
    std::experimental::optional<wl_resource*> const& surface,
    int32_t hotspot_x, int32_t hotspot_y)
{
    if (surface)
    {
        auto const cursor_stream = WlSurface::from(*surface)->stream;
        Displacement const cursor_hotspot{hotspot_x, hotspot_y};

        cursor = std::make_unique<WlStreamCursor>(get_session(client), cursor_stream, cursor_hotspot);
    }
    else
    {
        cursor = std::make_unique<WlHiddenCursor>(get_session(client));
    }

    if (focused_surface)
        cursor->apply_to(focused_surface.value());

    (void)serial;
}

void mf::WlPointer::release()
{
    destroy_wayland_object();
}

WlStreamCursor::WlStreamCursor(
    std::shared_ptr<mf::Session> const session,
    std::shared_ptr<mf::BufferStream> const& stream,
    Displacement hotspot) :
    session{session},
    stream{stream},
    hotspot{hotspot}
{
}

void WlStreamCursor::apply_to(mf::WlSurface* surface)
{
    auto id = surface->surface_id();
    if (id.as_value())
    {
        auto const mir_window = session->get_surface(id);
        mir_window->set_cursor_stream(stream, hotspot);
    }
}

WlHiddenCursor::WlHiddenCursor(
    std::shared_ptr<mf::Session> const session) :
    session{session}
{
}

void WlHiddenCursor::apply_to(mf::WlSurface* surface)
{
    auto id = surface->surface_id();
    if (id.as_value())
    {
        auto const mir_window = session->get_surface(id);
        mir_window->set_cursor_image({});
    }
}
