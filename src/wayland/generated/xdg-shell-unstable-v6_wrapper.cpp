/*
 * AUTOGENERATED - DO NOT EDIT
 *
 * This file is generated from xdg-shell-unstable-v6.xml
 * To regenerate, run the “refresh-wayland-wrapper” target.
 */

#include "xdg-shell-unstable-v6_wrapper.h"

#include <boost/throw_exception.hpp>
#include <boost/exception/diagnostic_information.hpp>

#include <wayland-server-core.h>

namespace mir
{
namespace wayland
{
extern struct wl_interface const wl_output_interface_data;
extern struct wl_interface const wl_seat_interface_data;
extern struct wl_interface const wl_surface_interface_data;
extern struct wl_interface const zxdg_popup_v6_interface_data;
extern struct wl_interface const zxdg_positioner_v6_interface_data;
extern struct wl_interface const zxdg_shell_v6_interface_data;
extern struct wl_interface const zxdg_surface_v6_interface_data;
extern struct wl_interface const zxdg_toplevel_v6_interface_data;
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

// XdgShellV6

struct mw::XdgShellV6::Thunks
{
    static int const supported_version;

    static void destroy_thunk(struct wl_client* client, struct wl_resource* resource)
    {
        try
        {
            wl_resource_destroy(resource);
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgShellV6::destroy()");
        }
    }

    static void create_positioner_thunk(struct wl_client* client, struct wl_resource* resource, uint32_t id)
    {
        wl_resource* id_resolved{
            wl_resource_create(client, &zxdg_positioner_v6_interface_data, wl_resource_get_version(resource), id)};
        if (id_resolved == nullptr)
        {
            wl_client_post_no_memory(client);
            BOOST_THROW_EXCEPTION((std::bad_alloc{}));
        }
        try
        {
            auto me = static_cast<XdgShellV6*>(wl_resource_get_user_data(resource));
            me->create_positioner(id_resolved);
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgShellV6::create_positioner()");
        }
    }

    static void get_xdg_surface_thunk(struct wl_client* client, struct wl_resource* resource, uint32_t id, struct wl_resource* surface)
    {
        wl_resource* id_resolved{
            wl_resource_create(client, &zxdg_surface_v6_interface_data, wl_resource_get_version(resource), id)};
        if (id_resolved == nullptr)
        {
            wl_client_post_no_memory(client);
            BOOST_THROW_EXCEPTION((std::bad_alloc{}));
        }
        try
        {
            auto me = static_cast<XdgShellV6*>(wl_resource_get_user_data(resource));
            me->get_xdg_surface(id_resolved, surface);
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgShellV6::get_xdg_surface()");
        }
    }

    static void pong_thunk(struct wl_client* client, struct wl_resource* resource, uint32_t serial)
    {
        try
        {
            auto me = static_cast<XdgShellV6*>(wl_resource_get_user_data(resource));
            me->pong(serial);
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgShellV6::pong()");
        }
    }

    static void resource_destroyed_thunk(wl_resource* resource)
    {
        delete static_cast<XdgShellV6*>(wl_resource_get_user_data(resource));
    }

    static void bind_thunk(struct wl_client* client, void* data, uint32_t version, uint32_t id)
    {
        auto me = static_cast<XdgShellV6::Global*>(data);
        auto resource = wl_resource_create(
            client,
            &zxdg_shell_v6_interface_data,
            std::min((int)version, Thunks::supported_version),
            id);
        if (resource == nullptr)
        {
            wl_client_post_no_memory(client);
            BOOST_THROW_EXCEPTION((std::bad_alloc{}));
        }
        try
        {
            me->bind(resource);
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgShellV6 global bind");
        }
    }

    static struct wl_interface const* create_positioner_types[];
    static struct wl_interface const* get_xdg_surface_types[];
    static struct wl_message const request_messages[];
    static struct wl_message const event_messages[];
    static void const* request_vtable[];
};

int const mw::XdgShellV6::Thunks::supported_version = 1;

mw::XdgShellV6::XdgShellV6(struct wl_resource* resource, Version<1>)
    : client{wl_resource_get_client(resource)},
      resource{resource}
{
    if (resource == nullptr)
    {
        BOOST_THROW_EXCEPTION((std::bad_alloc{}));
    }
    wl_resource_set_implementation(resource, Thunks::request_vtable, this, &Thunks::resource_destroyed_thunk);
}

mw::XdgShellV6::~XdgShellV6()
{
    wl_resource_set_implementation(resource, nullptr, nullptr, nullptr);
}

void mw::XdgShellV6::send_ping_event(uint32_t serial) const
{
    wl_resource_post_event(resource, Opcode::ping, serial);
}

bool mw::XdgShellV6::is_instance(wl_resource* resource)
{
    return wl_resource_instance_of(resource, &zxdg_shell_v6_interface_data, Thunks::request_vtable);
}

uint32_t const mw::XdgShellV6::Error::role;
uint32_t const mw::XdgShellV6::Error::defunct_surfaces;
uint32_t const mw::XdgShellV6::Error::not_the_topmost_popup;
uint32_t const mw::XdgShellV6::Error::invalid_popup_parent;
uint32_t const mw::XdgShellV6::Error::invalid_surface_state;
uint32_t const mw::XdgShellV6::Error::invalid_positioner;

mw::XdgShellV6::Global::Global(wl_display* display, Version<1>)
    : wayland::Global{
          wl_global_create(
              display,
              &zxdg_shell_v6_interface_data,
              Thunks::supported_version,
              this,
              &Thunks::bind_thunk)}
{
}

auto mw::XdgShellV6::Global::interface_name() const -> char const*
{
    return XdgShellV6::interface_name;
}

struct wl_interface const* mw::XdgShellV6::Thunks::create_positioner_types[] {
    &zxdg_positioner_v6_interface_data};

struct wl_interface const* mw::XdgShellV6::Thunks::get_xdg_surface_types[] {
    &zxdg_surface_v6_interface_data,
    &wl_surface_interface_data};

struct wl_message const mw::XdgShellV6::Thunks::request_messages[] {
    {"destroy", "", all_null_types},
    {"create_positioner", "n", create_positioner_types},
    {"get_xdg_surface", "no", get_xdg_surface_types},
    {"pong", "u", all_null_types}};

struct wl_message const mw::XdgShellV6::Thunks::event_messages[] {
    {"ping", "u", all_null_types}};

void const* mw::XdgShellV6::Thunks::request_vtable[] {
    (void*)Thunks::destroy_thunk,
    (void*)Thunks::create_positioner_thunk,
    (void*)Thunks::get_xdg_surface_thunk,
    (void*)Thunks::pong_thunk};

mw::XdgShellV6* mw::XdgShellV6::from(struct wl_resource* resource)
{
    if (wl_resource_instance_of(resource, &zxdg_shell_v6_interface_data, XdgShellV6::Thunks::request_vtable))
    {
        return static_cast<XdgShellV6*>(wl_resource_get_user_data(resource));
    }
    return nullptr;
}

// XdgPositionerV6

struct mw::XdgPositionerV6::Thunks
{
    static int const supported_version;

    static void destroy_thunk(struct wl_client* client, struct wl_resource* resource)
    {
        try
        {
            wl_resource_destroy(resource);
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgPositionerV6::destroy()");
        }
    }

    static void set_size_thunk(struct wl_client* client, struct wl_resource* resource, int32_t width, int32_t height)
    {
        try
        {
            auto me = static_cast<XdgPositionerV6*>(wl_resource_get_user_data(resource));
            me->set_size(width, height);
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgPositionerV6::set_size()");
        }
    }

    static void set_anchor_rect_thunk(struct wl_client* client, struct wl_resource* resource, int32_t x, int32_t y, int32_t width, int32_t height)
    {
        try
        {
            auto me = static_cast<XdgPositionerV6*>(wl_resource_get_user_data(resource));
            me->set_anchor_rect(x, y, width, height);
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgPositionerV6::set_anchor_rect()");
        }
    }

    static void set_anchor_thunk(struct wl_client* client, struct wl_resource* resource, uint32_t anchor)
    {
        try
        {
            auto me = static_cast<XdgPositionerV6*>(wl_resource_get_user_data(resource));
            me->set_anchor(anchor);
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgPositionerV6::set_anchor()");
        }
    }

    static void set_gravity_thunk(struct wl_client* client, struct wl_resource* resource, uint32_t gravity)
    {
        try
        {
            auto me = static_cast<XdgPositionerV6*>(wl_resource_get_user_data(resource));
            me->set_gravity(gravity);
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgPositionerV6::set_gravity()");
        }
    }

    static void set_constraint_adjustment_thunk(struct wl_client* client, struct wl_resource* resource, uint32_t constraint_adjustment)
    {
        try
        {
            auto me = static_cast<XdgPositionerV6*>(wl_resource_get_user_data(resource));
            me->set_constraint_adjustment(constraint_adjustment);
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgPositionerV6::set_constraint_adjustment()");
        }
    }

    static void set_offset_thunk(struct wl_client* client, struct wl_resource* resource, int32_t x, int32_t y)
    {
        try
        {
            auto me = static_cast<XdgPositionerV6*>(wl_resource_get_user_data(resource));
            me->set_offset(x, y);
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgPositionerV6::set_offset()");
        }
    }

    static void resource_destroyed_thunk(wl_resource* resource)
    {
        delete static_cast<XdgPositionerV6*>(wl_resource_get_user_data(resource));
    }

    static struct wl_message const request_messages[];
    static void const* request_vtable[];
};

int const mw::XdgPositionerV6::Thunks::supported_version = 1;

mw::XdgPositionerV6::XdgPositionerV6(struct wl_resource* resource, Version<1>)
    : client{wl_resource_get_client(resource)},
      resource{resource}
{
    if (resource == nullptr)
    {
        BOOST_THROW_EXCEPTION((std::bad_alloc{}));
    }
    wl_resource_set_implementation(resource, Thunks::request_vtable, this, &Thunks::resource_destroyed_thunk);
}

mw::XdgPositionerV6::~XdgPositionerV6()
{
    wl_resource_set_implementation(resource, nullptr, nullptr, nullptr);
}

bool mw::XdgPositionerV6::is_instance(wl_resource* resource)
{
    return wl_resource_instance_of(resource, &zxdg_positioner_v6_interface_data, Thunks::request_vtable);
}

uint32_t const mw::XdgPositionerV6::Error::invalid_input;
uint32_t const mw::XdgPositionerV6::Anchor::none;
uint32_t const mw::XdgPositionerV6::Anchor::top;
uint32_t const mw::XdgPositionerV6::Anchor::bottom;
uint32_t const mw::XdgPositionerV6::Anchor::left;
uint32_t const mw::XdgPositionerV6::Anchor::right;
uint32_t const mw::XdgPositionerV6::Gravity::none;
uint32_t const mw::XdgPositionerV6::Gravity::top;
uint32_t const mw::XdgPositionerV6::Gravity::bottom;
uint32_t const mw::XdgPositionerV6::Gravity::left;
uint32_t const mw::XdgPositionerV6::Gravity::right;
uint32_t const mw::XdgPositionerV6::ConstraintAdjustment::none;
uint32_t const mw::XdgPositionerV6::ConstraintAdjustment::slide_x;
uint32_t const mw::XdgPositionerV6::ConstraintAdjustment::slide_y;
uint32_t const mw::XdgPositionerV6::ConstraintAdjustment::flip_x;
uint32_t const mw::XdgPositionerV6::ConstraintAdjustment::flip_y;
uint32_t const mw::XdgPositionerV6::ConstraintAdjustment::resize_x;
uint32_t const mw::XdgPositionerV6::ConstraintAdjustment::resize_y;

struct wl_message const mw::XdgPositionerV6::Thunks::request_messages[] {
    {"destroy", "", all_null_types},
    {"set_size", "ii", all_null_types},
    {"set_anchor_rect", "iiii", all_null_types},
    {"set_anchor", "u", all_null_types},
    {"set_gravity", "u", all_null_types},
    {"set_constraint_adjustment", "u", all_null_types},
    {"set_offset", "ii", all_null_types}};

void const* mw::XdgPositionerV6::Thunks::request_vtable[] {
    (void*)Thunks::destroy_thunk,
    (void*)Thunks::set_size_thunk,
    (void*)Thunks::set_anchor_rect_thunk,
    (void*)Thunks::set_anchor_thunk,
    (void*)Thunks::set_gravity_thunk,
    (void*)Thunks::set_constraint_adjustment_thunk,
    (void*)Thunks::set_offset_thunk};

mw::XdgPositionerV6* mw::XdgPositionerV6::from(struct wl_resource* resource)
{
    if (wl_resource_instance_of(resource, &zxdg_positioner_v6_interface_data, XdgPositionerV6::Thunks::request_vtable))
    {
        return static_cast<XdgPositionerV6*>(wl_resource_get_user_data(resource));
    }
    return nullptr;
}

// XdgSurfaceV6

struct mw::XdgSurfaceV6::Thunks
{
    static int const supported_version;

    static void destroy_thunk(struct wl_client* client, struct wl_resource* resource)
    {
        try
        {
            wl_resource_destroy(resource);
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgSurfaceV6::destroy()");
        }
    }

    static void get_toplevel_thunk(struct wl_client* client, struct wl_resource* resource, uint32_t id)
    {
        wl_resource* id_resolved{
            wl_resource_create(client, &zxdg_toplevel_v6_interface_data, wl_resource_get_version(resource), id)};
        if (id_resolved == nullptr)
        {
            wl_client_post_no_memory(client);
            BOOST_THROW_EXCEPTION((std::bad_alloc{}));
        }
        try
        {
            auto me = static_cast<XdgSurfaceV6*>(wl_resource_get_user_data(resource));
            me->get_toplevel(id_resolved);
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgSurfaceV6::get_toplevel()");
        }
    }

    static void get_popup_thunk(struct wl_client* client, struct wl_resource* resource, uint32_t id, struct wl_resource* parent, struct wl_resource* positioner)
    {
        wl_resource* id_resolved{
            wl_resource_create(client, &zxdg_popup_v6_interface_data, wl_resource_get_version(resource), id)};
        if (id_resolved == nullptr)
        {
            wl_client_post_no_memory(client);
            BOOST_THROW_EXCEPTION((std::bad_alloc{}));
        }
        try
        {
            auto me = static_cast<XdgSurfaceV6*>(wl_resource_get_user_data(resource));
            me->get_popup(id_resolved, parent, positioner);
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgSurfaceV6::get_popup()");
        }
    }

    static void set_window_geometry_thunk(struct wl_client* client, struct wl_resource* resource, int32_t x, int32_t y, int32_t width, int32_t height)
    {
        try
        {
            auto me = static_cast<XdgSurfaceV6*>(wl_resource_get_user_data(resource));
            me->set_window_geometry(x, y, width, height);
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgSurfaceV6::set_window_geometry()");
        }
    }

    static void ack_configure_thunk(struct wl_client* client, struct wl_resource* resource, uint32_t serial)
    {
        try
        {
            auto me = static_cast<XdgSurfaceV6*>(wl_resource_get_user_data(resource));
            me->ack_configure(serial);
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgSurfaceV6::ack_configure()");
        }
    }

    static void resource_destroyed_thunk(wl_resource* resource)
    {
        delete static_cast<XdgSurfaceV6*>(wl_resource_get_user_data(resource));
    }

    static struct wl_interface const* get_toplevel_types[];
    static struct wl_interface const* get_popup_types[];
    static struct wl_message const request_messages[];
    static struct wl_message const event_messages[];
    static void const* request_vtable[];
};

int const mw::XdgSurfaceV6::Thunks::supported_version = 1;

mw::XdgSurfaceV6::XdgSurfaceV6(struct wl_resource* resource, Version<1>)
    : client{wl_resource_get_client(resource)},
      resource{resource}
{
    if (resource == nullptr)
    {
        BOOST_THROW_EXCEPTION((std::bad_alloc{}));
    }
    wl_resource_set_implementation(resource, Thunks::request_vtable, this, &Thunks::resource_destroyed_thunk);
}

mw::XdgSurfaceV6::~XdgSurfaceV6()
{
    wl_resource_set_implementation(resource, nullptr, nullptr, nullptr);
}

void mw::XdgSurfaceV6::send_configure_event(uint32_t serial) const
{
    wl_resource_post_event(resource, Opcode::configure, serial);
}

bool mw::XdgSurfaceV6::is_instance(wl_resource* resource)
{
    return wl_resource_instance_of(resource, &zxdg_surface_v6_interface_data, Thunks::request_vtable);
}

uint32_t const mw::XdgSurfaceV6::Error::not_constructed;
uint32_t const mw::XdgSurfaceV6::Error::already_constructed;
uint32_t const mw::XdgSurfaceV6::Error::unconfigured_buffer;

struct wl_interface const* mw::XdgSurfaceV6::Thunks::get_toplevel_types[] {
    &zxdg_toplevel_v6_interface_data};

struct wl_interface const* mw::XdgSurfaceV6::Thunks::get_popup_types[] {
    &zxdg_popup_v6_interface_data,
    &zxdg_surface_v6_interface_data,
    &zxdg_positioner_v6_interface_data};

struct wl_message const mw::XdgSurfaceV6::Thunks::request_messages[] {
    {"destroy", "", all_null_types},
    {"get_toplevel", "n", get_toplevel_types},
    {"get_popup", "noo", get_popup_types},
    {"set_window_geometry", "iiii", all_null_types},
    {"ack_configure", "u", all_null_types}};

struct wl_message const mw::XdgSurfaceV6::Thunks::event_messages[] {
    {"configure", "u", all_null_types}};

void const* mw::XdgSurfaceV6::Thunks::request_vtable[] {
    (void*)Thunks::destroy_thunk,
    (void*)Thunks::get_toplevel_thunk,
    (void*)Thunks::get_popup_thunk,
    (void*)Thunks::set_window_geometry_thunk,
    (void*)Thunks::ack_configure_thunk};

mw::XdgSurfaceV6* mw::XdgSurfaceV6::from(struct wl_resource* resource)
{
    if (wl_resource_instance_of(resource, &zxdg_surface_v6_interface_data, XdgSurfaceV6::Thunks::request_vtable))
    {
        return static_cast<XdgSurfaceV6*>(wl_resource_get_user_data(resource));
    }
    return nullptr;
}

// XdgToplevelV6

struct mw::XdgToplevelV6::Thunks
{
    static int const supported_version;

    static void destroy_thunk(struct wl_client* client, struct wl_resource* resource)
    {
        try
        {
            wl_resource_destroy(resource);
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgToplevelV6::destroy()");
        }
    }

    static void set_parent_thunk(struct wl_client* client, struct wl_resource* resource, struct wl_resource* parent)
    {
        std::optional<struct wl_resource*> parent_resolved;
        if (parent != nullptr)
        {
            parent_resolved = {parent};
        }
        try
        {
            auto me = static_cast<XdgToplevelV6*>(wl_resource_get_user_data(resource));
            me->set_parent(parent_resolved);
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgToplevelV6::set_parent()");
        }
    }

    static void set_title_thunk(struct wl_client* client, struct wl_resource* resource, char const* title)
    {
        try
        {
            auto me = static_cast<XdgToplevelV6*>(wl_resource_get_user_data(resource));
            me->set_title(title);
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgToplevelV6::set_title()");
        }
    }

    static void set_app_id_thunk(struct wl_client* client, struct wl_resource* resource, char const* app_id)
    {
        try
        {
            auto me = static_cast<XdgToplevelV6*>(wl_resource_get_user_data(resource));
            me->set_app_id(app_id);
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgToplevelV6::set_app_id()");
        }
    }

    static void show_window_menu_thunk(struct wl_client* client, struct wl_resource* resource, struct wl_resource* seat, uint32_t serial, int32_t x, int32_t y)
    {
        try
        {
            auto me = static_cast<XdgToplevelV6*>(wl_resource_get_user_data(resource));
            me->show_window_menu(seat, serial, x, y);
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgToplevelV6::show_window_menu()");
        }
    }

    static void move_thunk(struct wl_client* client, struct wl_resource* resource, struct wl_resource* seat, uint32_t serial)
    {
        try
        {
            auto me = static_cast<XdgToplevelV6*>(wl_resource_get_user_data(resource));
            me->move(seat, serial);
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgToplevelV6::move()");
        }
    }

    static void resize_thunk(struct wl_client* client, struct wl_resource* resource, struct wl_resource* seat, uint32_t serial, uint32_t edges)
    {
        try
        {
            auto me = static_cast<XdgToplevelV6*>(wl_resource_get_user_data(resource));
            me->resize(seat, serial, edges);
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgToplevelV6::resize()");
        }
    }

    static void set_max_size_thunk(struct wl_client* client, struct wl_resource* resource, int32_t width, int32_t height)
    {
        try
        {
            auto me = static_cast<XdgToplevelV6*>(wl_resource_get_user_data(resource));
            me->set_max_size(width, height);
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgToplevelV6::set_max_size()");
        }
    }

    static void set_min_size_thunk(struct wl_client* client, struct wl_resource* resource, int32_t width, int32_t height)
    {
        try
        {
            auto me = static_cast<XdgToplevelV6*>(wl_resource_get_user_data(resource));
            me->set_min_size(width, height);
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgToplevelV6::set_min_size()");
        }
    }

    static void set_maximized_thunk(struct wl_client* client, struct wl_resource* resource)
    {
        try
        {
            auto me = static_cast<XdgToplevelV6*>(wl_resource_get_user_data(resource));
            me->set_maximized();
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgToplevelV6::set_maximized()");
        }
    }

    static void unset_maximized_thunk(struct wl_client* client, struct wl_resource* resource)
    {
        try
        {
            auto me = static_cast<XdgToplevelV6*>(wl_resource_get_user_data(resource));
            me->unset_maximized();
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgToplevelV6::unset_maximized()");
        }
    }

    static void set_fullscreen_thunk(struct wl_client* client, struct wl_resource* resource, struct wl_resource* output)
    {
        std::optional<struct wl_resource*> output_resolved;
        if (output != nullptr)
        {
            output_resolved = {output};
        }
        try
        {
            auto me = static_cast<XdgToplevelV6*>(wl_resource_get_user_data(resource));
            me->set_fullscreen(output_resolved);
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgToplevelV6::set_fullscreen()");
        }
    }

    static void unset_fullscreen_thunk(struct wl_client* client, struct wl_resource* resource)
    {
        try
        {
            auto me = static_cast<XdgToplevelV6*>(wl_resource_get_user_data(resource));
            me->unset_fullscreen();
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgToplevelV6::unset_fullscreen()");
        }
    }

    static void set_minimized_thunk(struct wl_client* client, struct wl_resource* resource)
    {
        try
        {
            auto me = static_cast<XdgToplevelV6*>(wl_resource_get_user_data(resource));
            me->set_minimized();
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgToplevelV6::set_minimized()");
        }
    }

    static void resource_destroyed_thunk(wl_resource* resource)
    {
        delete static_cast<XdgToplevelV6*>(wl_resource_get_user_data(resource));
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

int const mw::XdgToplevelV6::Thunks::supported_version = 1;

mw::XdgToplevelV6::XdgToplevelV6(struct wl_resource* resource, Version<1>)
    : client{wl_resource_get_client(resource)},
      resource{resource}
{
    if (resource == nullptr)
    {
        BOOST_THROW_EXCEPTION((std::bad_alloc{}));
    }
    wl_resource_set_implementation(resource, Thunks::request_vtable, this, &Thunks::resource_destroyed_thunk);
}

mw::XdgToplevelV6::~XdgToplevelV6()
{
    wl_resource_set_implementation(resource, nullptr, nullptr, nullptr);
}

void mw::XdgToplevelV6::send_configure_event(int32_t width, int32_t height, struct wl_array* states) const
{
    wl_resource_post_event(resource, Opcode::configure, width, height, states);
}

void mw::XdgToplevelV6::send_close_event() const
{
    wl_resource_post_event(resource, Opcode::close);
}

bool mw::XdgToplevelV6::is_instance(wl_resource* resource)
{
    return wl_resource_instance_of(resource, &zxdg_toplevel_v6_interface_data, Thunks::request_vtable);
}

uint32_t const mw::XdgToplevelV6::ResizeEdge::none;
uint32_t const mw::XdgToplevelV6::ResizeEdge::top;
uint32_t const mw::XdgToplevelV6::ResizeEdge::bottom;
uint32_t const mw::XdgToplevelV6::ResizeEdge::left;
uint32_t const mw::XdgToplevelV6::ResizeEdge::top_left;
uint32_t const mw::XdgToplevelV6::ResizeEdge::bottom_left;
uint32_t const mw::XdgToplevelV6::ResizeEdge::right;
uint32_t const mw::XdgToplevelV6::ResizeEdge::top_right;
uint32_t const mw::XdgToplevelV6::ResizeEdge::bottom_right;
uint32_t const mw::XdgToplevelV6::State::maximized;
uint32_t const mw::XdgToplevelV6::State::fullscreen;
uint32_t const mw::XdgToplevelV6::State::resizing;
uint32_t const mw::XdgToplevelV6::State::activated;

struct wl_interface const* mw::XdgToplevelV6::Thunks::set_parent_types[] {
    &zxdg_toplevel_v6_interface_data};

struct wl_interface const* mw::XdgToplevelV6::Thunks::show_window_menu_types[] {
    &wl_seat_interface_data,
    nullptr,
    nullptr,
    nullptr};

struct wl_interface const* mw::XdgToplevelV6::Thunks::move_types[] {
    &wl_seat_interface_data,
    nullptr};

struct wl_interface const* mw::XdgToplevelV6::Thunks::resize_types[] {
    &wl_seat_interface_data,
    nullptr,
    nullptr};

struct wl_interface const* mw::XdgToplevelV6::Thunks::set_fullscreen_types[] {
    &wl_output_interface_data};

struct wl_message const mw::XdgToplevelV6::Thunks::request_messages[] {
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

struct wl_message const mw::XdgToplevelV6::Thunks::event_messages[] {
    {"configure", "iia", all_null_types},
    {"close", "", all_null_types}};

void const* mw::XdgToplevelV6::Thunks::request_vtable[] {
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

mw::XdgToplevelV6* mw::XdgToplevelV6::from(struct wl_resource* resource)
{
    if (wl_resource_instance_of(resource, &zxdg_toplevel_v6_interface_data, XdgToplevelV6::Thunks::request_vtable))
    {
        return static_cast<XdgToplevelV6*>(wl_resource_get_user_data(resource));
    }
    return nullptr;
}

// XdgPopupV6

struct mw::XdgPopupV6::Thunks
{
    static int const supported_version;

    static void destroy_thunk(struct wl_client* client, struct wl_resource* resource)
    {
        try
        {
            wl_resource_destroy(resource);
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgPopupV6::destroy()");
        }
    }

    static void grab_thunk(struct wl_client* client, struct wl_resource* resource, struct wl_resource* seat, uint32_t serial)
    {
        try
        {
            auto me = static_cast<XdgPopupV6*>(wl_resource_get_user_data(resource));
            me->grab(seat, serial);
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgPopupV6::grab()");
        }
    }

    static void resource_destroyed_thunk(wl_resource* resource)
    {
        delete static_cast<XdgPopupV6*>(wl_resource_get_user_data(resource));
    }

    static struct wl_interface const* grab_types[];
    static struct wl_message const request_messages[];
    static struct wl_message const event_messages[];
    static void const* request_vtable[];
};

int const mw::XdgPopupV6::Thunks::supported_version = 1;

mw::XdgPopupV6::XdgPopupV6(struct wl_resource* resource, Version<1>)
    : client{wl_resource_get_client(resource)},
      resource{resource}
{
    if (resource == nullptr)
    {
        BOOST_THROW_EXCEPTION((std::bad_alloc{}));
    }
    wl_resource_set_implementation(resource, Thunks::request_vtable, this, &Thunks::resource_destroyed_thunk);
}

mw::XdgPopupV6::~XdgPopupV6()
{
    wl_resource_set_implementation(resource, nullptr, nullptr, nullptr);
}

void mw::XdgPopupV6::send_configure_event(int32_t x, int32_t y, int32_t width, int32_t height) const
{
    wl_resource_post_event(resource, Opcode::configure, x, y, width, height);
}

void mw::XdgPopupV6::send_popup_done_event() const
{
    wl_resource_post_event(resource, Opcode::popup_done);
}

bool mw::XdgPopupV6::is_instance(wl_resource* resource)
{
    return wl_resource_instance_of(resource, &zxdg_popup_v6_interface_data, Thunks::request_vtable);
}

uint32_t const mw::XdgPopupV6::Error::invalid_grab;

struct wl_interface const* mw::XdgPopupV6::Thunks::grab_types[] {
    &wl_seat_interface_data,
    nullptr};

struct wl_message const mw::XdgPopupV6::Thunks::request_messages[] {
    {"destroy", "", all_null_types},
    {"grab", "ou", grab_types}};

struct wl_message const mw::XdgPopupV6::Thunks::event_messages[] {
    {"configure", "iiii", all_null_types},
    {"popup_done", "", all_null_types}};

void const* mw::XdgPopupV6::Thunks::request_vtable[] {
    (void*)Thunks::destroy_thunk,
    (void*)Thunks::grab_thunk};

mw::XdgPopupV6* mw::XdgPopupV6::from(struct wl_resource* resource)
{
    if (wl_resource_instance_of(resource, &zxdg_popup_v6_interface_data, XdgPopupV6::Thunks::request_vtable))
    {
        return static_cast<XdgPopupV6*>(wl_resource_get_user_data(resource));
    }
    return nullptr;
}

namespace mir
{
namespace wayland
{

struct wl_interface const zxdg_shell_v6_interface_data {
    mw::XdgShellV6::interface_name,
    mw::XdgShellV6::Thunks::supported_version,
    4, mw::XdgShellV6::Thunks::request_messages,
    1, mw::XdgShellV6::Thunks::event_messages};

struct wl_interface const zxdg_positioner_v6_interface_data {
    mw::XdgPositionerV6::interface_name,
    mw::XdgPositionerV6::Thunks::supported_version,
    7, mw::XdgPositionerV6::Thunks::request_messages,
    0, nullptr};

struct wl_interface const zxdg_surface_v6_interface_data {
    mw::XdgSurfaceV6::interface_name,
    mw::XdgSurfaceV6::Thunks::supported_version,
    5, mw::XdgSurfaceV6::Thunks::request_messages,
    1, mw::XdgSurfaceV6::Thunks::event_messages};

struct wl_interface const zxdg_toplevel_v6_interface_data {
    mw::XdgToplevelV6::interface_name,
    mw::XdgToplevelV6::Thunks::supported_version,
    14, mw::XdgToplevelV6::Thunks::request_messages,
    2, mw::XdgToplevelV6::Thunks::event_messages};

struct wl_interface const zxdg_popup_v6_interface_data {
    mw::XdgPopupV6::interface_name,
    mw::XdgPopupV6::Thunks::supported_version,
    2, mw::XdgPopupV6::Thunks::request_messages,
    2, mw::XdgPopupV6::Thunks::event_messages};

}
}
