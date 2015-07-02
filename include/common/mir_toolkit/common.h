/*
 * Simple definitions common to client and server.
 *
 * Copyright © 2013-2014 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Author: Daniel van Vugt <daniel.van.vugt@canonical.com>
 */

#ifndef MIR_COMMON_H_
#define MIR_COMMON_H_

/**
 * \addtogroup mir_toolkit
 * @{
 */
/* This is C code. Not C++. */

/**
 * Attributes of a surface that the client and server/shell may wish to
 * get or set over the wire.
 */
typedef enum MirSurfaceAttrib
{
    /* Do not specify values...code relies on 0...N ordering. */
    mir_surface_attrib_type,
    mir_surface_attrib_state,
    mir_surface_attrib_swapinterval,
    mir_surface_attrib_focus,
    mir_surface_attrib_dpi,
    mir_surface_attrib_visibility,
    mir_surface_attrib_preferred_orientation,
    /* Must be last */
    mir_surface_attribs
} MirSurfaceAttrib;

typedef enum MirSurfaceType
{
    mir_surface_type_normal,       /**< AKA "regular"                       */
    mir_surface_type_utility,      /**< AKA "floating"                      */
    mir_surface_type_dialog,
    mir_surface_type_overlay,      /**< \deprecated  Use "gloss" instead.   */
    mir_surface_type_gloss = mir_surface_type_overlay,
    mir_surface_type_freestyle,
    mir_surface_type_popover,      /**< \deprecated  Choose "menu" or "tip" */
    mir_surface_type_menu = mir_surface_type_popover,
    mir_surface_type_inputmethod,  /**< AKA "OSK" or handwriting etc.       */
    mir_surface_type_satellite,    /**< AKA "toolbox"/"toolbar"             */
    mir_surface_type_tip,          /**< AKA "tooltip"                       */
    mir_surface_types
} MirSurfaceType;

typedef enum MirSurfaceState
{
    mir_surface_state_unknown,
    mir_surface_state_restored,
    mir_surface_state_minimized,
    mir_surface_state_maximized,
    mir_surface_state_vertmaximized,
    /* mir_surface_state_semimaximized,
       Omitted for now, since it's functionally a subset of vertmaximized and
       differs only in the X coordinate. */
    mir_surface_state_fullscreen,
    mir_surface_state_horizmaximized,
    mir_surface_state_hidden,
    mir_surface_states
} MirSurfaceState;

/* TODO: MirSurfaceFocusState MirSurfaceVisibility and MirLifecycleState use an inconsistent
   naming convention. */
typedef enum MirSurfaceFocusState
{
    mir_surface_unfocused = 0,
    mir_surface_focused
} MirSurfaceFocusState;

typedef enum MirSurfaceVisibility
{
    mir_surface_visibility_occluded = 0,
    mir_surface_visibility_exposed
} MirSurfaceVisibility;

typedef enum MirLifecycleState
{
    mir_lifecycle_state_will_suspend,
    mir_lifecycle_state_resumed,
    mir_lifecycle_connection_lost
} MirLifecycleState;

typedef enum MirPowerMode
{
    mir_power_mode_on, /* Display in use. */
    mir_power_mode_standby, /* Blanked, low power. */
    mir_power_mode_suspend, /* Blanked, lowest power. */
    mir_power_mode_off /* Powered down. */
} MirPowerMode;

typedef enum MirPromptSessionState
{
    mir_prompt_session_state_stopped = 0,
    mir_prompt_session_state_started,
    mir_prompt_session_state_suspended
} MirPromptSessionState;

/**
 * The order of components in a format enum matches the
 * order of the components as they would be written in an
 *  integer representing a pixel value of that format.
 *
 * For example, abgr_8888 corresponds to 0xAABBGGRR, which will
 * end up as R,G,B,A in memory in a little endian system, and
 * as A,B,G,R in memory in a big endian system.
 */
typedef enum MirPixelFormat
{
    mir_pixel_format_invalid,
    mir_pixel_format_abgr_8888,
    mir_pixel_format_xbgr_8888,
    mir_pixel_format_argb_8888,
    mir_pixel_format_xrgb_8888,
    mir_pixel_format_bgr_888,
    mir_pixel_format_rgb_565,
    mir_pixel_format_bgr_565,
    mir_pixel_formats
} MirPixelFormat;

/* This could be improved... https://bugs.launchpad.net/mir/+bug/1236254 */
#define MIR_BYTES_PER_PIXEL(f) ((f) == mir_pixel_format_bgr_888 ? 3 : \
                                (f) == mir_pixel_format_rgb_565 ? 2 : \
                                (f) == mir_pixel_format_bgr_565 ? 2 : \
                                                                  4)

/** Direction relative to the "natural" orientation of the display */
typedef enum MirOrientation
{
    mir_orientation_normal = 0,
    mir_orientation_left = 90,
    mir_orientation_inverted = 180,
    mir_orientation_right = 270
} MirOrientation;

typedef enum MirOrientationMode
{
    mir_orientation_mode_portrait = 1 << 0,
    mir_orientation_mode_landscape = 1 << 1,
    mir_orientation_mode_portrait_inverted = 1 << 2,
    mir_orientation_mode_landscape_inverted = 1 << 3,
    mir_orientation_mode_portrait_any = mir_orientation_mode_portrait |
                                        mir_orientation_mode_portrait_inverted,
    mir_orientation_mode_landscape_any = mir_orientation_mode_landscape |
                                         mir_orientation_mode_landscape_inverted,
    mir_orientation_mode_any = mir_orientation_mode_portrait_any |
                               mir_orientation_mode_landscape_any
} MirOrientationMode;

typedef enum MirEdgeAttachment
{
    mir_edge_attachment_vertical = 1 << 0,
    mir_edge_attachment_horizontal = 1 << 1,
    mir_edge_attachment_any = mir_edge_attachment_vertical |
                              mir_edge_attachment_horizontal
} MirEdgeAttachment;
/**@}*/

#endif
