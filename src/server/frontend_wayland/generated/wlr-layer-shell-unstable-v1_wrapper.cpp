/*
 * AUTOGENERATED - DO NOT EDIT
 *
 * This file is generated from wlr-layer-shell-unstable-v1.xml
 * To regenerate, run the “refresh-wayland-wrapper” target.
 */

#include "wlr-layer-shell-unstable-v1_wrapper.h"

#include <boost/throw_exception.hpp>
#include <boost/exception/diagnostic_information.hpp>

#include <wayland-server-core.h>

#include "mir/log.h"

namespace
{
void internal_error_processing_request(struct wl_client* client, std::string const& method_name)
{
#if (WAYLAND_VERSION_MAJOR > 1 || (WAYLAND_VERSION_MAJOR == 1 && WAYLAND_VERSION_MINOR > 16))
    wl_client_post_implementation_error(
        client,
        "Mir internal error processing %s request",
        method_name.c_str(),
        "Exception processing " + method_name + " request");
#else
    wl_client_post_no_memory(client);
#endif
    ::mir::log(
        ::mir::logging::Severity::error,
        "frontend:Wayland",
        std::current_exception(),
        "Exception processing " + method_name + " request");
}
}

namespace mir
{
namespace frontend
{
namespace wayland
{
extern struct wl_interface const wl_output_interface_data;
extern struct wl_interface const wl_surface_interface_data;
extern struct wl_interface const xdg_popup_interface_data;
extern struct wl_interface const zwlr_layer_shell_v1_interface_data;
extern struct wl_interface const zwlr_layer_surface_v1_interface_data;
}
}
}

namespace mfw = mir::frontend::wayland;

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

// LayerShellV1

mfw::LayerShellV1* mfw::LayerShellV1::from(struct wl_resource* resource)
{
    return static_cast<LayerShellV1*>(wl_resource_get_user_data(resource));
}

struct mfw::LayerShellV1::Thunks
{
    static void get_layer_surface_thunk(struct wl_client* client, struct wl_resource* resource, uint32_t id, struct wl_resource* surface, struct wl_resource* output, uint32_t layer, char const* namespace_)
    {
        auto me = static_cast<LayerShellV1*>(wl_resource_get_user_data(resource));
        std::experimental::optional<struct wl_resource*> output_resolved;
        if (output != nullptr)
        {
            output_resolved = {output};
        }
        try
        {
            me->get_layer_surface(client, resource, id, surface, output_resolved, layer, namespace_);
        }
        catch(...)
        {
            internal_error_processing_request(client, "LayerShellV1::get_layer_surface()");
        }
    }

    static void bind_thunk(struct wl_client* client, void* data, uint32_t version, uint32_t id)
    {
        auto me = static_cast<LayerShellV1*>(data);
        auto resource = wl_resource_create(client, &zwlr_layer_shell_v1_interface_data,
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
            internal_error_processing_request(client, "LayerShellV1::bind()");
        }
    }

    static struct wl_interface const* get_layer_surface_types[];
    static struct wl_message const request_messages[];
    static void const* request_vtable[];
};

mfw::LayerShellV1::LayerShellV1(struct wl_display* display, uint32_t max_version)
    : global{wl_global_create(display, &zwlr_layer_shell_v1_interface_data, max_version, this, &Thunks::bind_thunk)},
      max_version{max_version}
{
    if (global == nullptr)
    {
        BOOST_THROW_EXCEPTION((std::runtime_error{"Failed to export zwlr_layer_shell_v1 interface"}));
    }
}

mfw::LayerShellV1::~LayerShellV1()
{
    wl_global_destroy(global);
}

void mfw::LayerShellV1::destroy_wayland_object(struct wl_resource* resource) const
{
    wl_resource_destroy(resource);
}

struct wl_interface const* mfw::LayerShellV1::Thunks::get_layer_surface_types[] {
    &zwlr_layer_surface_v1_interface_data,
    &wl_surface_interface_data,
    &wl_output_interface_data,
    nullptr,
    nullptr};

struct wl_message const mfw::LayerShellV1::Thunks::request_messages[] {
    {"get_layer_surface", "no?ous", get_layer_surface_types}};

void const* mfw::LayerShellV1::Thunks::request_vtable[] {
    (void*)Thunks::get_layer_surface_thunk};

// LayerSurfaceV1

mfw::LayerSurfaceV1* mfw::LayerSurfaceV1::from(struct wl_resource* resource)
{
    return static_cast<LayerSurfaceV1*>(wl_resource_get_user_data(resource));
}

struct mfw::LayerSurfaceV1::Thunks
{
    static void set_size_thunk(struct wl_client* client, struct wl_resource* resource, uint32_t width, uint32_t height)
    {
        auto me = static_cast<LayerSurfaceV1*>(wl_resource_get_user_data(resource));
        try
        {
            me->set_size(width, height);
        }
        catch(...)
        {
            internal_error_processing_request(client, "LayerSurfaceV1::set_size()");
        }
    }

    static void set_anchor_thunk(struct wl_client* client, struct wl_resource* resource, uint32_t anchor)
    {
        auto me = static_cast<LayerSurfaceV1*>(wl_resource_get_user_data(resource));
        try
        {
            me->set_anchor(anchor);
        }
        catch(...)
        {
            internal_error_processing_request(client, "LayerSurfaceV1::set_anchor()");
        }
    }

    static void set_exclusive_zone_thunk(struct wl_client* client, struct wl_resource* resource, int32_t zone)
    {
        auto me = static_cast<LayerSurfaceV1*>(wl_resource_get_user_data(resource));
        try
        {
            me->set_exclusive_zone(zone);
        }
        catch(...)
        {
            internal_error_processing_request(client, "LayerSurfaceV1::set_exclusive_zone()");
        }
    }

    static void set_margin_thunk(struct wl_client* client, struct wl_resource* resource, int32_t top, int32_t right, int32_t bottom, int32_t left)
    {
        auto me = static_cast<LayerSurfaceV1*>(wl_resource_get_user_data(resource));
        try
        {
            me->set_margin(top, right, bottom, left);
        }
        catch(...)
        {
            internal_error_processing_request(client, "LayerSurfaceV1::set_margin()");
        }
    }

    static void set_keyboard_interactivity_thunk(struct wl_client* client, struct wl_resource* resource, uint32_t keyboard_interactivity)
    {
        auto me = static_cast<LayerSurfaceV1*>(wl_resource_get_user_data(resource));
        try
        {
            me->set_keyboard_interactivity(keyboard_interactivity);
        }
        catch(...)
        {
            internal_error_processing_request(client, "LayerSurfaceV1::set_keyboard_interactivity()");
        }
    }

    static void get_popup_thunk(struct wl_client* client, struct wl_resource* resource, struct wl_resource* popup)
    {
        auto me = static_cast<LayerSurfaceV1*>(wl_resource_get_user_data(resource));
        try
        {
            me->get_popup(popup);
        }
        catch(...)
        {
            internal_error_processing_request(client, "LayerSurfaceV1::get_popup()");
        }
    }

    static void ack_configure_thunk(struct wl_client* client, struct wl_resource* resource, uint32_t serial)
    {
        auto me = static_cast<LayerSurfaceV1*>(wl_resource_get_user_data(resource));
        try
        {
            me->ack_configure(serial);
        }
        catch(...)
        {
            internal_error_processing_request(client, "LayerSurfaceV1::ack_configure()");
        }
    }

    static void destroy_thunk(struct wl_client* client, struct wl_resource* resource)
    {
        auto me = static_cast<LayerSurfaceV1*>(wl_resource_get_user_data(resource));
        try
        {
            me->destroy();
        }
        catch(...)
        {
            internal_error_processing_request(client, "LayerSurfaceV1::destroy()");
        }
    }

    static void resource_destroyed_thunk(wl_resource* resource)
    {
        delete static_cast<LayerSurfaceV1*>(wl_resource_get_user_data(resource));
    }

    static struct wl_interface const* get_popup_types[];
    static struct wl_message const request_messages[];
    static struct wl_message const event_messages[];
    static void const* request_vtable[];
};

mfw::LayerSurfaceV1::LayerSurfaceV1(struct wl_client* client, struct wl_resource* parent, uint32_t id)
    : client{client},
      resource{wl_resource_create(client, &zwlr_layer_surface_v1_interface_data, wl_resource_get_version(parent), id)}
{
    if (resource == nullptr)
    {
        wl_resource_post_no_memory(parent);
        BOOST_THROW_EXCEPTION((std::bad_alloc{}));
    }
    wl_resource_set_implementation(resource, Thunks::request_vtable, this, &Thunks::resource_destroyed_thunk);
}

void mfw::LayerSurfaceV1::send_configure_event(uint32_t serial, uint32_t width, uint32_t height) const
{
    wl_resource_post_event(resource, Opcode::configure, serial, width, height);
}

void mfw::LayerSurfaceV1::send_closed_event() const
{
    wl_resource_post_event(resource, Opcode::closed);
}

void mfw::LayerSurfaceV1::destroy_wayland_object() const
{
    wl_resource_destroy(resource);
}

struct wl_interface const* mfw::LayerSurfaceV1::Thunks::get_popup_types[] {
    &xdg_popup_interface_data};

struct wl_message const mfw::LayerSurfaceV1::Thunks::request_messages[] {
    {"set_size", "uu", all_null_types},
    {"set_anchor", "u", all_null_types},
    {"set_exclusive_zone", "i", all_null_types},
    {"set_margin", "iiii", all_null_types},
    {"set_keyboard_interactivity", "u", all_null_types},
    {"get_popup", "o", get_popup_types},
    {"ack_configure", "u", all_null_types},
    {"destroy", "", all_null_types}};

struct wl_message const mfw::LayerSurfaceV1::Thunks::event_messages[] {
    {"configure", "uuu", all_null_types},
    {"closed", "", all_null_types}};

void const* mfw::LayerSurfaceV1::Thunks::request_vtable[] {
    (void*)Thunks::set_size_thunk,
    (void*)Thunks::set_anchor_thunk,
    (void*)Thunks::set_exclusive_zone_thunk,
    (void*)Thunks::set_margin_thunk,
    (void*)Thunks::set_keyboard_interactivity_thunk,
    (void*)Thunks::get_popup_thunk,
    (void*)Thunks::ack_configure_thunk,
    (void*)Thunks::destroy_thunk};

namespace mir
{
namespace frontend
{
namespace wayland
{

struct wl_interface const zwlr_layer_shell_v1_interface_data {
    "zwlr_layer_shell_v1", 1,
    1, mfw::LayerShellV1::Thunks::request_messages,
    0, nullptr};

struct wl_interface const zwlr_layer_surface_v1_interface_data {
    "zwlr_layer_surface_v1", 1,
    8, mfw::LayerSurfaceV1::Thunks::request_messages,
    2, mfw::LayerSurfaceV1::Thunks::event_messages};

}
}
}
