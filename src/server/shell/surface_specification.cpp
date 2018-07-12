/*
 * Copyright © 2015 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 or 3,
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
 * Authored By: Christopher James Halse Rogers <christopher.halse.rogers@canonical.com
 */

#include "mir/shell/surface_specification.h"
#include "mir/scene/surface_creation_parameters.h"

namespace msh = mir::shell;

bool msh::SurfaceSpecification::is_empty() const
{
    // You know, compile-time reflection would be pretty
    // useful here :)
    return !width.is_set() &&
        !height.is_set() &&
        !pixel_format.is_set() &&
        !buffer_usage.is_set() &&
        !name.is_set() &&
        !output_id.is_set() &&
        !type.is_set() &&
        !state.is_set() &&
        !preferred_orientation.is_set() &&
        !parent_id.is_set() &&
        !aux_rect.is_set() &&
        !edge_attachment.is_set() &&
        !min_width.is_set() &&
        !min_height.is_set() &&
        !max_width.is_set() &&
        !max_height.is_set() &&
        !width_inc.is_set() &&
        !height_inc.is_set() &&
        !min_aspect.is_set() &&
        !max_aspect.is_set() &&
        !streams.is_set() &&
        !parent.is_set() &&
        !input_shape.is_set() &&
        !shell_chrome.is_set();
}

msh::SurfaceParameters::SurfaceParameters(mir::scene::SurfaceCreationParameters const& params)
{
    top_left = params.top_left;
    size = params.size;
    name = params.name;
    output_id = params.output_id.as_value();
    type = params.type;
    state = params.state;
    preferred_orientation = params.preferred_orientation;
    aux_rect = params.aux_rect;
    placement_hints = params.placement_hints;
    surface_placement_gravity = params.surface_placement_gravity;
    aux_rect_placement_gravity = params.aux_rect_placement_gravity;
    if (params.aux_rect_placement_offset_x.is_set() && params.aux_rect_placement_offset_y.is_set())
        aux_rect_placement_offset = geometry::Displacement{params.aux_rect_placement_offset_x.value(),
                                                           params.aux_rect_placement_offset_y.value()};
    min_width = params.min_width;
    min_height = params.min_height;
    max_width = params.max_width;
    max_height = params.max_height;
    width_inc = params.width_inc;
    height_inc = params.height_inc;
    min_aspect = params.min_aspect;
    max_aspect = params.max_aspect;
    parent = params.parent;
    input_shape = params.input_shape;
    input_mode = params.input_mode;
    shell_chrome = params.shell_chrome;
    confine_pointer = params.confine_pointer;
    pixel_format = params.pixel_format;
    buffer_usage = params.buffer_usage;
    parent_id = params.parent_id;
    content_id = params.content_id;
    edge_attachment = params.edge_attachment;
    streams = params.streams;

    if (params.edge_attachment.is_set() && !placement_hints.is_set())
    {
        switch (params.edge_attachment.value())
        {
        case mir_edge_attachment_vertical:
            surface_placement_gravity = mir_placement_gravity_northwest;
            aux_rect_placement_gravity = mir_placement_gravity_northeast;
            placement_hints = mir_placement_hints_flip_x;
            break;

        case mir_edge_attachment_horizontal:
            surface_placement_gravity = mir_placement_gravity_northwest;
            aux_rect_placement_gravity = mir_placement_gravity_southwest;
            placement_hints = mir_placement_hints_flip_y;
            break;

        case mir_edge_attachment_any:
            surface_placement_gravity = mir_placement_gravity_northwest;
            aux_rect_placement_gravity = mir_placement_gravity_northeast;
            placement_hints = mir_placement_hints_flip_any;
            break;
        }
    }
}

msh::SurfaceParameters::SurfaceParameters(msh::SurfaceSpecification const& params)
{
    if (params.width.is_set() && params.height.is_set())
        size = geometry::Size{params.width.value(), params.height.value()};
    name = params.name;
    output_id = params.output_id;
    type = params.type;
    state = params.state;
    preferred_orientation = params.preferred_orientation;
    aux_rect = params.aux_rect;
    placement_hints = params.placement_hints;
    surface_placement_gravity = params.surface_placement_gravity;
    aux_rect_placement_gravity = params.aux_rect_placement_gravity;
    if (params.aux_rect_placement_offset_x.is_set() && params.aux_rect_placement_offset_y.is_set())
        aux_rect_placement_offset = geometry::Displacement{params.aux_rect_placement_offset_x.value(),
                                                           params.aux_rect_placement_offset_y.value()};
    min_width = params.min_width;
    min_height = params.min_height;
    max_width = params.max_width;
    max_height = params.max_height;
    width_inc = params.width_inc;
    height_inc = params.height_inc;
    min_aspect = params.min_aspect;
    max_aspect = params.max_aspect;
    parent = params.parent;
    input_shape = params.input_shape;
    shell_chrome = params.shell_chrome;
    confine_pointer = params.confine_pointer;
    pixel_format = params.pixel_format;
    buffer_usage = params.buffer_usage;
    parent_id = params.parent_id;
    edge_attachment = params.edge_attachment;
    streams = params.streams;
    cursor_image = params.cursor_image;
    stream_cursor = params.stream_cursor;

    if (params.edge_attachment.is_set() && !placement_hints.is_set())
    {
        switch (params.edge_attachment.value())
        {
        case mir_edge_attachment_vertical:
            surface_placement_gravity = mir_placement_gravity_northwest;
            aux_rect_placement_gravity = mir_placement_gravity_northeast;
            placement_hints = mir_placement_hints_flip_x;
            break;

        case mir_edge_attachment_horizontal:
            surface_placement_gravity = mir_placement_gravity_northwest;
            aux_rect_placement_gravity = mir_placement_gravity_southwest;
            placement_hints = mir_placement_hints_flip_y;
            break;

        case mir_edge_attachment_any:
            surface_placement_gravity = mir_placement_gravity_northwest;
            aux_rect_placement_gravity = mir_placement_gravity_northeast;
            placement_hints = MirPlacementHints(mir_placement_hints_flip_any | mir_placement_hints_antipodes);
            break;
        }
    }
}

void msh::SurfaceParameters::update_from(mir::scene::SurfaceCreationParameters const& params)
{
    top_left = params.top_left;
    size = params.size;
    name = params.name;
    parent = params.parent;
    pixel_format = params.pixel_format;
    buffer_usage = params.buffer_usage;
    input_mode = params.input_mode;

    output_id = params.output_id.as_value();
    if (params.type.is_set())
        type = params.type;
    if (params.state.is_set())
        state = params.state;
    if (params.preferred_orientation.is_set())
        preferred_orientation = params.preferred_orientation;
    if (params.aux_rect.is_set())
        aux_rect = params.aux_rect;
    if (params.placement_hints.is_set())
        placement_hints = params.placement_hints;
    if (params.surface_placement_gravity.is_set())
        surface_placement_gravity = params.surface_placement_gravity;
    if (params.aux_rect_placement_gravity.is_set())
        aux_rect_placement_gravity = params.aux_rect_placement_gravity;
    if (params.aux_rect_placement_offset_x.is_set() && params.aux_rect_placement_offset_y.is_set())
        aux_rect_placement_offset = geometry::Displacement{params.aux_rect_placement_offset_x.value(),
                                                           params.aux_rect_placement_offset_y.value()};
    if (params.min_width.is_set())
        min_width = params.min_width;
    if (params.min_height.is_set())
        min_height = params.min_height;
    if (params.max_width.is_set())
        max_width = params.max_width;
    if (params.max_height.is_set())
        max_height = params.max_height;
    if (params.width_inc.is_set())
        width_inc = params.width_inc;
    if (params.height_inc.is_set())
        height_inc = params.height_inc;
    if (params.min_aspect.is_set())
        min_aspect = params.min_aspect;
    if (params.max_aspect.is_set())
        max_aspect = params.max_aspect;
    if (params.input_shape.is_set())
        input_shape = params.input_shape;
    if (params.shell_chrome.is_set())
        shell_chrome = params.shell_chrome;
    if (params.confine_pointer.is_set())
        confine_pointer = params.confine_pointer;
    if (params.parent_id.is_set())
        parent_id = params.parent_id;
    if (params.content_id.is_set())
        content_id = params.content_id;
    if (params.edge_attachment.is_set())
        edge_attachment = params.edge_attachment;
    if (params.streams.is_set())
        streams = params.streams;
}
