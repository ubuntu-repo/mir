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
 * Authored by: William Wold <william.wold@canonical.com>
 */

#include "layer_shell_v1.h"

#include "wl_surface.h"
#include "window_wl_surface_role.h"

namespace mf = mir::frontend;
namespace geom = mir::geometry;

namespace mir
{
namespace frontend
{

class LayerSurfaceV1 : public wayland::LayerSurfaceV1, public WindowWlSurfaceRole
{
public:
    LayerSurfaceV1(struct wl_client* client, struct wl_resource* parent_resource, uint32_t id, WlSurface* surface,
                   LayerShellV1 const& layer_shell);
    ~LayerSurfaceV1() = default;

private:
    // from wayland::LayerSurfaceV1
    void set_size(uint32_t width, uint32_t height) override;
    void set_anchor(uint32_t anchor) override;
    void set_exclusive_zone(int32_t zone) override;
    void set_margin(int32_t top, int32_t right, int32_t bottom, int32_t left) override;
    void set_keyboard_interactivity(uint32_t keyboard_interactivity) override;
    void get_popup(struct wl_resource* popup) override;
    void ack_configure(uint32_t serial) override;
    void destroy() override;

    // from WindowWlSurfaceRole
    void handle_resize(std::experimental::optional<geometry::Point> const& new_top_left,
                       geometry::Size const& new_size) override;
};

}
}

// LayerShellV1

mf::LayerShellV1::LayerShellV1(struct wl_display* display, std::shared_ptr<Shell> const shell, WlSeat& seat,
                               OutputManager* output_manager)
    : wayland::LayerShellV1(display, 1),
      shell{shell},
      seat{seat},
      output_manager{output_manager}
{
}

void mf::LayerShellV1::get_layer_surface(struct wl_client* client, struct wl_resource* resource, uint32_t id,
                                         struct wl_resource* surface,
                                         std::experimental::optional<struct wl_resource*> const& output,
                                         uint32_t layer, std::string const& namespace_)
{
    (void)output;
    (void)layer;
    (void)namespace_;
    new LayerSurfaceV1(client, resource, id, WlSurface::from(surface), *this);
}

// LayerSurfaceV1

mf::LayerSurfaceV1::LayerSurfaceV1(struct wl_client* client, struct wl_resource* parent_resource, uint32_t id,
                                   WlSurface* surface, LayerShellV1 const& layer_shell)
    : wayland::LayerSurfaceV1(client, parent_resource, id),
      WindowWlSurfaceRole(&layer_shell.seat, client, surface, layer_shell.shell, layer_shell.output_manager)
{
}

void mf::LayerSurfaceV1::set_size(uint32_t width, uint32_t height)
{
    (void)width;
    (void)height;
}

void mf::LayerSurfaceV1::set_anchor(uint32_t anchor)
{
    (void)anchor;
}

void mf::LayerSurfaceV1::set_exclusive_zone(int32_t zone)
{
    (void)zone;
}

void mf::LayerSurfaceV1::set_margin(int32_t top, int32_t right, int32_t bottom, int32_t left)
{
    (void)top;
    (void)right;
    (void)bottom;
    (void)left;
}

void mf::LayerSurfaceV1::set_keyboard_interactivity(uint32_t keyboard_interactivity)
{
    (void)keyboard_interactivity;
}

void mf::LayerSurfaceV1::get_popup(struct wl_resource* popup)
{
    (void)popup;
}

void mf::LayerSurfaceV1::ack_configure(uint32_t serial)
{
    (void)serial;
}

void mf::LayerSurfaceV1::destroy()
{
    destroy_wayland_object();
}

void mf::LayerSurfaceV1::handle_resize(std::experimental::optional<geometry::Point> const& new_top_left,
                                       geometry::Size const& new_size)
{
    (void)new_top_left;
    (void)new_size;
}
