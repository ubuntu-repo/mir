/*
 * AUTOGENERATED - DO NOT EDIT
 *
 * This file is generated from xdg-shell.xml
 * To regenerate, run the “refresh-wayland-wrapper” target.
 */

#include "xdg-shell_wrapper.h"

#include <boost/throw_exception.hpp>
#include <boost/exception/diagnostic_information.hpp>

#include <wayland-server-core.h>

#include "mir/log.h"

namespace mir
{
namespace wayland
{
extern struct wl_interface const wl_output_interface_data;
extern struct wl_interface const wl_seat_interface_data;
extern struct wl_interface const wl_surface_interface_data;
extern struct wl_interface const xdg_popup_interface_data;
extern struct wl_interface const xdg_positioner_interface_data;
extern struct wl_interface const xdg_surface_interface_data;
extern struct wl_interface const xdg_toplevel_interface_data;
extern struct wl_interface const xdg_wm_base_interface_data;
}
}

namespace mw = mir::wayland;

namespace
{
struct wl_interface const* all_null_types [] {
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr};
}

// XdgWmBase

mw::XdgWmBase* mw::XdgWmBase::from(struct wl_resource* resource)
{
    return static_cast<XdgWmBase*>(wl_resource_get_user_data(resource));
}

struct mw::XdgWmBase::Thunks
{
    static void destroy_thunk(struct wl_client* client, struct wl_resource* resource)
    {
        auto me = static_cast<XdgWmBase*>(wl_resource_get_user_data(resource));
        try
        {
            me->destroy(client, resource);
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgWmBase::destroy() request");
        }
    }

    static void create_positioner_thunk(struct wl_client* client, struct wl_resource* resource, uint32_t id)
    {
        auto me = static_cast<XdgWmBase*>(wl_resource_get_user_data(resource));
        try
        {
            me->create_positioner(client, resource, id);
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgWmBase::create_positioner() request");
        }
    }

    static void get_xdg_surface_thunk(struct wl_client* client, struct wl_resource* resource, uint32_t id, struct wl_resource* surface)
    {
        auto me = static_cast<XdgWmBase*>(wl_resource_get_user_data(resource));
        try
        {
            me->get_xdg_surface(client, resource, id, surface);
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgWmBase::get_xdg_surface() request");
        }
    }

    static void pong_thunk(struct wl_client* client, struct wl_resource* resource, uint32_t serial)
    {
        auto me = static_cast<XdgWmBase*>(wl_resource_get_user_data(resource));
        try
        {
            me->pong(client, resource, serial);
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgWmBase::pong() request");
        }
    }

    static void bind_thunk(struct wl_client* client, void* data, uint32_t version, uint32_t id)
    {
        auto me = static_cast<XdgWmBase*>(data);
        auto resource = wl_resource_create(client, &xdg_wm_base_interface_data,
                                           std::min(version, me->max_version), id);
        if (resource == nullptr)
        {
            wl_client_post_no_memory(client);
            BOOST_THROW_EXCEPTION((std::bad_alloc{}));
        }
        wl_resource_set_implementation(resource, Thunks::request_vtable, me, nullptr);
        try
        {
            me->bind(client, resource);
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgWmBase::bind() request");
        }
    }

    static struct wl_interface const* create_positioner_types[];
    static struct wl_interface const* get_xdg_surface_types[];
    static struct wl_message const request_messages[];
    static struct wl_message const event_messages[];
    static void const* request_vtable[];
};

mw::XdgWmBase::XdgWmBase(struct wl_display* display, uint32_t max_version)
    : global{wl_global_create(display, &xdg_wm_base_interface_data, max_version, this, &Thunks::bind_thunk)},
      max_version{max_version}
{
    if (global == nullptr)
    {
        BOOST_THROW_EXCEPTION((std::runtime_error{"Failed to export xdg_wm_base interface"}));
    }
}

mw::XdgWmBase::~XdgWmBase()
{
    wl_global_destroy(global);
}

void mw::XdgWmBase::send_ping_event(struct wl_resource* resource, uint32_t serial) const
{
    wl_resource_post_event(resource, Opcode::ping, serial);
}

void mw::XdgWmBase::destroy_wayland_object(struct wl_resource* resource) const
{
    wl_resource_destroy(resource);
}

struct wl_interface const* mw::XdgWmBase::Thunks::create_positioner_types[] {
    &xdg_positioner_interface_data};

struct wl_interface const* mw::XdgWmBase::Thunks::get_xdg_surface_types[] {
    &xdg_surface_interface_data,
    &wl_surface_interface_data};

struct wl_message const mw::XdgWmBase::Thunks::request_messages[] {
    {"destroy", "", all_null_types},
    {"create_positioner", "n", create_positioner_types},
    {"get_xdg_surface", "no", get_xdg_surface_types},
    {"pong", "u", all_null_types}};

struct wl_message const mw::XdgWmBase::Thunks::event_messages[] {
    {"ping", "u", all_null_types}};

void const* mw::XdgWmBase::Thunks::request_vtable[] {
    (void*)Thunks::destroy_thunk,
    (void*)Thunks::create_positioner_thunk,
    (void*)Thunks::get_xdg_surface_thunk,
    (void*)Thunks::pong_thunk};

// XdgPositioner

mw::XdgPositioner* mw::XdgPositioner::from(struct wl_resource* resource)
{
    return static_cast<XdgPositioner*>(wl_resource_get_user_data(resource));
}

struct mw::XdgPositioner::Thunks
{
    static void destroy_thunk(struct wl_client*, struct wl_resource* resource)
    {
        auto me = static_cast<XdgPositioner*>(wl_resource_get_user_data(resource));
        try
        {
            me->destroy();
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgPositioner::destroy() request");
        }
    }

    static void set_size_thunk(struct wl_client*, struct wl_resource* resource, int32_t width, int32_t height)
    {
        auto me = static_cast<XdgPositioner*>(wl_resource_get_user_data(resource));
        try
        {
            me->set_size(width, height);
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgPositioner::set_size() request");
        }
    }

    static void set_anchor_rect_thunk(struct wl_client*, struct wl_resource* resource, int32_t x, int32_t y, int32_t width, int32_t height)
    {
        auto me = static_cast<XdgPositioner*>(wl_resource_get_user_data(resource));
        try
        {
            me->set_anchor_rect(x, y, width, height);
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgPositioner::set_anchor_rect() request");
        }
    }

    static void set_anchor_thunk(struct wl_client*, struct wl_resource* resource, uint32_t anchor)
    {
        auto me = static_cast<XdgPositioner*>(wl_resource_get_user_data(resource));
        try
        {
            me->set_anchor(anchor);
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgPositioner::set_anchor() request");
        }
    }

    static void set_gravity_thunk(struct wl_client*, struct wl_resource* resource, uint32_t gravity)
    {
        auto me = static_cast<XdgPositioner*>(wl_resource_get_user_data(resource));
        try
        {
            me->set_gravity(gravity);
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgPositioner::set_gravity() request");
        }
    }

    static void set_constraint_adjustment_thunk(struct wl_client*, struct wl_resource* resource, uint32_t constraint_adjustment)
    {
        auto me = static_cast<XdgPositioner*>(wl_resource_get_user_data(resource));
        try
        {
            me->set_constraint_adjustment(constraint_adjustment);
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgPositioner::set_constraint_adjustment() request");
        }
    }

    static void set_offset_thunk(struct wl_client*, struct wl_resource* resource, int32_t x, int32_t y)
    {
        auto me = static_cast<XdgPositioner*>(wl_resource_get_user_data(resource));
        try
        {
            me->set_offset(x, y);
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgPositioner::set_offset() request");
        }
    }

    static void resource_destroyed_thunk(wl_resource* resource)
    {
        delete static_cast<XdgPositioner*>(wl_resource_get_user_data(resource));
    }

    static struct wl_message const request_messages[];
    static void const* request_vtable[];
};

mw::XdgPositioner::XdgPositioner(struct wl_client* client, struct wl_resource* parent, uint32_t id)
    : client{client},
      resource{wl_resource_create(client, &xdg_positioner_interface_data, wl_resource_get_version(parent), id)}
{
    if (resource == nullptr)
    {
        wl_resource_post_no_memory(parent);
        BOOST_THROW_EXCEPTION((std::bad_alloc{}));
    }
    wl_resource_set_implementation(resource, Thunks::request_vtable, this, &Thunks::resource_destroyed_thunk);
}

bool mw::XdgPositioner::is_instance(wl_resource* resource)
{
    return wl_resource_instance_of(resource, &xdg_positioner_interface_data, Thunks::request_vtable);
}

void mw::XdgPositioner::destroy_wayland_object() const
{
    wl_resource_destroy(resource);
}

struct wl_message const mw::XdgPositioner::Thunks::request_messages[] {
    {"destroy", "", all_null_types},
    {"set_size", "ii", all_null_types},
    {"set_anchor_rect", "iiii", all_null_types},
    {"set_anchor", "u", all_null_types},
    {"set_gravity", "u", all_null_types},
    {"set_constraint_adjustment", "u", all_null_types},
    {"set_offset", "ii", all_null_types}};

void const* mw::XdgPositioner::Thunks::request_vtable[] {
    (void*)Thunks::destroy_thunk,
    (void*)Thunks::set_size_thunk,
    (void*)Thunks::set_anchor_rect_thunk,
    (void*)Thunks::set_anchor_thunk,
    (void*)Thunks::set_gravity_thunk,
    (void*)Thunks::set_constraint_adjustment_thunk,
    (void*)Thunks::set_offset_thunk};

// XdgSurface

mw::XdgSurface* mw::XdgSurface::from(struct wl_resource* resource)
{
    return static_cast<XdgSurface*>(wl_resource_get_user_data(resource));
}

struct mw::XdgSurface::Thunks
{
    static void destroy_thunk(struct wl_client*, struct wl_resource* resource)
    {
        auto me = static_cast<XdgSurface*>(wl_resource_get_user_data(resource));
        try
        {
            me->destroy();
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgSurface::destroy() request");
        }
    }

    static void get_toplevel_thunk(struct wl_client*, struct wl_resource* resource, uint32_t id)
    {
        auto me = static_cast<XdgSurface*>(wl_resource_get_user_data(resource));
        try
        {
            me->get_toplevel(id);
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgSurface::get_toplevel() request");
        }
    }

    static void get_popup_thunk(struct wl_client*, struct wl_resource* resource, uint32_t id, struct wl_resource* parent, struct wl_resource* positioner)
    {
        auto me = static_cast<XdgSurface*>(wl_resource_get_user_data(resource));
        std::experimental::optional<struct wl_resource*> parent_resolved;
        if (parent != nullptr)
        {
            parent_resolved = {parent};
        }
        try
        {
            me->get_popup(id, parent_resolved, positioner);
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgSurface::get_popup() request");
        }
    }

    static void set_window_geometry_thunk(struct wl_client*, struct wl_resource* resource, int32_t x, int32_t y, int32_t width, int32_t height)
    {
        auto me = static_cast<XdgSurface*>(wl_resource_get_user_data(resource));
        try
        {
            me->set_window_geometry(x, y, width, height);
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgSurface::set_window_geometry() request");
        }
    }

    static void ack_configure_thunk(struct wl_client*, struct wl_resource* resource, uint32_t serial)
    {
        auto me = static_cast<XdgSurface*>(wl_resource_get_user_data(resource));
        try
        {
            me->ack_configure(serial);
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgSurface::ack_configure() request");
        }
    }

    static void resource_destroyed_thunk(wl_resource* resource)
    {
        delete static_cast<XdgSurface*>(wl_resource_get_user_data(resource));
    }

    static struct wl_interface const* get_toplevel_types[];
    static struct wl_interface const* get_popup_types[];
    static struct wl_message const request_messages[];
    static struct wl_message const event_messages[];
    static void const* request_vtable[];
};

mw::XdgSurface::XdgSurface(struct wl_client* client, struct wl_resource* parent, uint32_t id)
    : client{client},
      resource{wl_resource_create(client, &xdg_surface_interface_data, wl_resource_get_version(parent), id)}
{
    if (resource == nullptr)
    {
        wl_resource_post_no_memory(parent);
        BOOST_THROW_EXCEPTION((std::bad_alloc{}));
    }
    wl_resource_set_implementation(resource, Thunks::request_vtable, this, &Thunks::resource_destroyed_thunk);
}

void mw::XdgSurface::send_configure_event(uint32_t serial) const
{
    wl_resource_post_event(resource, Opcode::configure, serial);
}

bool mw::XdgSurface::is_instance(wl_resource* resource)
{
    return wl_resource_instance_of(resource, &xdg_surface_interface_data, Thunks::request_vtable);
}

void mw::XdgSurface::destroy_wayland_object() const
{
    wl_resource_destroy(resource);
}

struct wl_interface const* mw::XdgSurface::Thunks::get_toplevel_types[] {
    &xdg_toplevel_interface_data};

struct wl_interface const* mw::XdgSurface::Thunks::get_popup_types[] {
    &xdg_popup_interface_data,
    &xdg_surface_interface_data,
    &xdg_positioner_interface_data};

struct wl_message const mw::XdgSurface::Thunks::request_messages[] {
    {"destroy", "", all_null_types},
    {"get_toplevel", "n", get_toplevel_types},
    {"get_popup", "n?oo", get_popup_types},
    {"set_window_geometry", "iiii", all_null_types},
    {"ack_configure", "u", all_null_types}};

struct wl_message const mw::XdgSurface::Thunks::event_messages[] {
    {"configure", "u", all_null_types}};

void const* mw::XdgSurface::Thunks::request_vtable[] {
    (void*)Thunks::destroy_thunk,
    (void*)Thunks::get_toplevel_thunk,
    (void*)Thunks::get_popup_thunk,
    (void*)Thunks::set_window_geometry_thunk,
    (void*)Thunks::ack_configure_thunk};

// XdgToplevel

mw::XdgToplevel* mw::XdgToplevel::from(struct wl_resource* resource)
{
    return static_cast<XdgToplevel*>(wl_resource_get_user_data(resource));
}

struct mw::XdgToplevel::Thunks
{
    static void destroy_thunk(struct wl_client*, struct wl_resource* resource)
    {
        auto me = static_cast<XdgToplevel*>(wl_resource_get_user_data(resource));
        try
        {
            me->destroy();
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgToplevel::destroy() request");
        }
    }

    static void set_parent_thunk(struct wl_client*, struct wl_resource* resource, struct wl_resource* parent)
    {
        auto me = static_cast<XdgToplevel*>(wl_resource_get_user_data(resource));
        std::experimental::optional<struct wl_resource*> parent_resolved;
        if (parent != nullptr)
        {
            parent_resolved = {parent};
        }
        try
        {
            me->set_parent(parent_resolved);
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgToplevel::set_parent() request");
        }
    }

    static void set_title_thunk(struct wl_client*, struct wl_resource* resource, char const* title)
    {
        auto me = static_cast<XdgToplevel*>(wl_resource_get_user_data(resource));
        try
        {
            me->set_title(title);
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgToplevel::set_title() request");
        }
    }

    static void set_app_id_thunk(struct wl_client*, struct wl_resource* resource, char const* app_id)
    {
        auto me = static_cast<XdgToplevel*>(wl_resource_get_user_data(resource));
        try
        {
            me->set_app_id(app_id);
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgToplevel::set_app_id() request");
        }
    }

    static void show_window_menu_thunk(struct wl_client*, struct wl_resource* resource, struct wl_resource* seat, uint32_t serial, int32_t x, int32_t y)
    {
        auto me = static_cast<XdgToplevel*>(wl_resource_get_user_data(resource));
        try
        {
            me->show_window_menu(seat, serial, x, y);
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgToplevel::show_window_menu() request");
        }
    }

    static void move_thunk(struct wl_client*, struct wl_resource* resource, struct wl_resource* seat, uint32_t serial)
    {
        auto me = static_cast<XdgToplevel*>(wl_resource_get_user_data(resource));
        try
        {
            me->move(seat, serial);
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgToplevel::move() request");
        }
    }

    static void resize_thunk(struct wl_client*, struct wl_resource* resource, struct wl_resource* seat, uint32_t serial, uint32_t edges)
    {
        auto me = static_cast<XdgToplevel*>(wl_resource_get_user_data(resource));
        try
        {
            me->resize(seat, serial, edges);
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgToplevel::resize() request");
        }
    }

    static void set_max_size_thunk(struct wl_client*, struct wl_resource* resource, int32_t width, int32_t height)
    {
        auto me = static_cast<XdgToplevel*>(wl_resource_get_user_data(resource));
        try
        {
            me->set_max_size(width, height);
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgToplevel::set_max_size() request");
        }
    }

    static void set_min_size_thunk(struct wl_client*, struct wl_resource* resource, int32_t width, int32_t height)
    {
        auto me = static_cast<XdgToplevel*>(wl_resource_get_user_data(resource));
        try
        {
            me->set_min_size(width, height);
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgToplevel::set_min_size() request");
        }
    }

    static void set_maximized_thunk(struct wl_client*, struct wl_resource* resource)
    {
        auto me = static_cast<XdgToplevel*>(wl_resource_get_user_data(resource));
        try
        {
            me->set_maximized();
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgToplevel::set_maximized() request");
        }
    }

    static void unset_maximized_thunk(struct wl_client*, struct wl_resource* resource)
    {
        auto me = static_cast<XdgToplevel*>(wl_resource_get_user_data(resource));
        try
        {
            me->unset_maximized();
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgToplevel::unset_maximized() request");
        }
    }

    static void set_fullscreen_thunk(struct wl_client*, struct wl_resource* resource, struct wl_resource* output)
    {
        auto me = static_cast<XdgToplevel*>(wl_resource_get_user_data(resource));
        std::experimental::optional<struct wl_resource*> output_resolved;
        if (output != nullptr)
        {
            output_resolved = {output};
        }
        try
        {
            me->set_fullscreen(output_resolved);
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgToplevel::set_fullscreen() request");
        }
    }

    static void unset_fullscreen_thunk(struct wl_client*, struct wl_resource* resource)
    {
        auto me = static_cast<XdgToplevel*>(wl_resource_get_user_data(resource));
        try
        {
            me->unset_fullscreen();
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgToplevel::unset_fullscreen() request");
        }
    }

    static void set_minimized_thunk(struct wl_client*, struct wl_resource* resource)
    {
        auto me = static_cast<XdgToplevel*>(wl_resource_get_user_data(resource));
        try
        {
            me->set_minimized();
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgToplevel::set_minimized() request");
        }
    }

    static void resource_destroyed_thunk(wl_resource* resource)
    {
        delete static_cast<XdgToplevel*>(wl_resource_get_user_data(resource));
    }

    static struct wl_interface const* set_parent_types[];
    static struct wl_interface const* show_window_menu_types[];
    static struct wl_interface const* move_types[];
    static struct wl_interface const* resize_types[];
    static struct wl_interface const* set_fullscreen_types[];
    static struct wl_message const request_messages[];
    static struct wl_message const event_messages[];
    static void const* request_vtable[];
};

mw::XdgToplevel::XdgToplevel(struct wl_client* client, struct wl_resource* parent, uint32_t id)
    : client{client},
      resource{wl_resource_create(client, &xdg_toplevel_interface_data, wl_resource_get_version(parent), id)}
{
    if (resource == nullptr)
    {
        wl_resource_post_no_memory(parent);
        BOOST_THROW_EXCEPTION((std::bad_alloc{}));
    }
    wl_resource_set_implementation(resource, Thunks::request_vtable, this, &Thunks::resource_destroyed_thunk);
}

void mw::XdgToplevel::send_configure_event(int32_t width, int32_t height, struct wl_array* states) const
{
    wl_resource_post_event(resource, Opcode::configure, width, height, states);
}

void mw::XdgToplevel::send_close_event() const
{
    wl_resource_post_event(resource, Opcode::close);
}

bool mw::XdgToplevel::is_instance(wl_resource* resource)
{
    return wl_resource_instance_of(resource, &xdg_toplevel_interface_data, Thunks::request_vtable);
}

void mw::XdgToplevel::destroy_wayland_object() const
{
    wl_resource_destroy(resource);
}

struct wl_interface const* mw::XdgToplevel::Thunks::set_parent_types[] {
    &xdg_toplevel_interface_data};

struct wl_interface const* mw::XdgToplevel::Thunks::show_window_menu_types[] {
    &wl_seat_interface_data,
    nullptr,
    nullptr,
    nullptr};

struct wl_interface const* mw::XdgToplevel::Thunks::move_types[] {
    &wl_seat_interface_data,
    nullptr};

struct wl_interface const* mw::XdgToplevel::Thunks::resize_types[] {
    &wl_seat_interface_data,
    nullptr,
    nullptr};

struct wl_interface const* mw::XdgToplevel::Thunks::set_fullscreen_types[] {
    &wl_output_interface_data};

struct wl_message const mw::XdgToplevel::Thunks::request_messages[] {
    {"destroy", "", all_null_types},
    {"set_parent", "?o", set_parent_types},
    {"set_title", "s", all_null_types},
    {"set_app_id", "s", all_null_types},
    {"show_window_menu", "ouii", show_window_menu_types},
    {"move", "ou", move_types},
    {"resize", "ouu", resize_types},
    {"set_max_size", "ii", all_null_types},
    {"set_min_size", "ii", all_null_types},
    {"set_maximized", "", all_null_types},
    {"unset_maximized", "", all_null_types},
    {"set_fullscreen", "?o", set_fullscreen_types},
    {"unset_fullscreen", "", all_null_types},
    {"set_minimized", "", all_null_types}};

struct wl_message const mw::XdgToplevel::Thunks::event_messages[] {
    {"configure", "iia", all_null_types},
    {"close", "", all_null_types}};

void const* mw::XdgToplevel::Thunks::request_vtable[] {
    (void*)Thunks::destroy_thunk,
    (void*)Thunks::set_parent_thunk,
    (void*)Thunks::set_title_thunk,
    (void*)Thunks::set_app_id_thunk,
    (void*)Thunks::show_window_menu_thunk,
    (void*)Thunks::move_thunk,
    (void*)Thunks::resize_thunk,
    (void*)Thunks::set_max_size_thunk,
    (void*)Thunks::set_min_size_thunk,
    (void*)Thunks::set_maximized_thunk,
    (void*)Thunks::unset_maximized_thunk,
    (void*)Thunks::set_fullscreen_thunk,
    (void*)Thunks::unset_fullscreen_thunk,
    (void*)Thunks::set_minimized_thunk};

// XdgPopup

mw::XdgPopup* mw::XdgPopup::from(struct wl_resource* resource)
{
    return static_cast<XdgPopup*>(wl_resource_get_user_data(resource));
}

struct mw::XdgPopup::Thunks
{
    static void destroy_thunk(struct wl_client*, struct wl_resource* resource)
    {
        auto me = static_cast<XdgPopup*>(wl_resource_get_user_data(resource));
        try
        {
            me->destroy();
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgPopup::destroy() request");
        }
    }

    static void grab_thunk(struct wl_client*, struct wl_resource* resource, struct wl_resource* seat, uint32_t serial)
    {
        auto me = static_cast<XdgPopup*>(wl_resource_get_user_data(resource));
        try
        {
            me->grab(seat, serial);
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgPopup::grab() request");
        }
    }

    static void resource_destroyed_thunk(wl_resource* resource)
    {
        delete static_cast<XdgPopup*>(wl_resource_get_user_data(resource));
    }

    static struct wl_interface const* grab_types[];
    static struct wl_message const request_messages[];
    static struct wl_message const event_messages[];
    static void const* request_vtable[];
};

mw::XdgPopup::XdgPopup(struct wl_client* client, struct wl_resource* parent, uint32_t id)
    : client{client},
      resource{wl_resource_create(client, &xdg_popup_interface_data, wl_resource_get_version(parent), id)}
{
    if (resource == nullptr)
    {
        wl_resource_post_no_memory(parent);
        BOOST_THROW_EXCEPTION((std::bad_alloc{}));
    }
    wl_resource_set_implementation(resource, Thunks::request_vtable, this, &Thunks::resource_destroyed_thunk);
}

void mw::XdgPopup::send_configure_event(int32_t x, int32_t y, int32_t width, int32_t height) const
{
    wl_resource_post_event(resource, Opcode::configure, x, y, width, height);
}

void mw::XdgPopup::send_popup_done_event() const
{
    wl_resource_post_event(resource, Opcode::popup_done);
}

bool mw::XdgPopup::is_instance(wl_resource* resource)
{
    return wl_resource_instance_of(resource, &xdg_popup_interface_data, Thunks::request_vtable);
}

void mw::XdgPopup::destroy_wayland_object() const
{
    wl_resource_destroy(resource);
}

struct wl_interface const* mw::XdgPopup::Thunks::grab_types[] {
    &wl_seat_interface_data,
    nullptr};

struct wl_message const mw::XdgPopup::Thunks::request_messages[] {
    {"destroy", "", all_null_types},
    {"grab", "ou", grab_types}};

struct wl_message const mw::XdgPopup::Thunks::event_messages[] {
    {"configure", "iiii", all_null_types},
    {"popup_done", "", all_null_types}};

void const* mw::XdgPopup::Thunks::request_vtable[] {
    (void*)Thunks::destroy_thunk,
    (void*)Thunks::grab_thunk};

namespace mir
{
namespace wayland
{

struct wl_interface const xdg_wm_base_interface_data {
    mw::XdgWmBase::interface_name,
    mw::XdgWmBase::interface_version,
    4, mw::XdgWmBase::Thunks::request_messages,
    1, mw::XdgWmBase::Thunks::event_messages};

struct wl_interface const xdg_positioner_interface_data {
    mw::XdgPositioner::interface_name,
    mw::XdgPositioner::interface_version,
    7, mw::XdgPositioner::Thunks::request_messages,
    0, nullptr};

struct wl_interface const xdg_surface_interface_data {
    mw::XdgSurface::interface_name,
    mw::XdgSurface::interface_version,
    5, mw::XdgSurface::Thunks::request_messages,
    1, mw::XdgSurface::Thunks::event_messages};

struct wl_interface const xdg_toplevel_interface_data {
    mw::XdgToplevel::interface_name,
    mw::XdgToplevel::interface_version,
    14, mw::XdgToplevel::Thunks::request_messages,
    2, mw::XdgToplevel::Thunks::event_messages};

struct wl_interface const xdg_popup_interface_data {
    mw::XdgPopup::interface_name,
    mw::XdgPopup::interface_version,
    2, mw::XdgPopup::Thunks::request_messages,
    2, mw::XdgPopup::Thunks::event_messages};

}
}
