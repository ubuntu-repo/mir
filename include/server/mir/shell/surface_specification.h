/*
 * Copyright © 2015-2016 Canonical Ltd.
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
 * Authored By: Alan Griffiths <alan@octopull.co.uk>
 */

#ifndef MIR_SHELL_SURFACE_SPECIFICATION_H_
#define MIR_SHELL_SURFACE_SPECIFICATION_H_

#include "mir/optional_value.h"
#include "mir_toolkit/common.h"
#include "mir/frontend/surface_id.h"
#include "mir/frontend/buffer_stream_id.h"
#include "mir/geometry/point.h"
#include "mir/geometry/displacement.h"
#include "mir/graphics/buffer_properties.h"
#include "mir/graphics/display_configuration.h"

#include <string>
#include <memory>

namespace mir
{
namespace graphics { class CursorImage; }
namespace scene { class Surface; }

namespace shell
{
struct SurfaceAspectRatio { unsigned width; unsigned height; };

struct StreamSpecification
{
    frontend::BufferStreamId stream_id;
    geometry::Displacement displacement;
    optional_value<geometry::Size> size;
};

struct StreamCursor
{
    frontend::BufferStreamId stream_id;
    geometry::Displacement hotspot;
};

/// Specification of surface properties requested by client
struct SurfaceSpecification
{
    bool is_empty() const;
    void update_from(SurfaceSpecification const& that);

    optional_value<geometry::Width> width;
    optional_value<geometry::Height> height;
    optional_value<MirPixelFormat> pixel_format;
    optional_value<graphics::BufferUsage> buffer_usage;
    optional_value<std::string> name;
    optional_value<graphics::DisplayConfigurationOutputId> output_id;
    optional_value<MirWindowType> type;
    optional_value<MirWindowState> state;
    optional_value<MirOrientationMode> preferred_orientation;
    optional_value<frontend::SurfaceId> parent_id;
    optional_value<geometry::Rectangle> aux_rect;
    optional_value<MirEdgeAttachment> edge_attachment;
    optional_value<MirPlacementHints> placement_hints;
    optional_value<MirPlacementGravity> surface_placement_gravity;
    optional_value<MirPlacementGravity> aux_rect_placement_gravity;
    optional_value<int> aux_rect_placement_offset_x;
    optional_value<int> aux_rect_placement_offset_y;
    optional_value<geometry::Width> min_width;
    optional_value<geometry::Height> min_height;
    optional_value<geometry::Width> max_width;
    optional_value<geometry::Height> max_height;
    optional_value<geometry::DeltaX> width_inc;
    optional_value<geometry::DeltaY> height_inc;
    optional_value<SurfaceAspectRatio> min_aspect;
    optional_value<SurfaceAspectRatio> max_aspect;
    optional_value<std::vector<StreamSpecification>> streams;
    optional_value<std::weak_ptr<scene::Surface>> parent;

    optional_value<std::vector<geometry::Rectangle>> input_shape;

    // TODO scene::SurfaceCreationParameters overlaps this content but has additional fields:
    //    geometry::Point top_left;
    //    input::InputReceptionMode input_mode;
    //
    //    it also has size instead of width + height
    // Maybe SurfaceCreationParameters /HasA/ SurfaceSpecification?
    optional_value<MirShellChrome> shell_chrome;
    optional_value<MirPointerConfinementState> confine_pointer;
    optional_value<std::shared_ptr<graphics::CursorImage>> cursor_image;
    optional_value<StreamCursor> stream_cursor;

    // used for anchored surfaces
    optional_value<MirPlacementGravity> anchor_edge;
    optional_value<int> anchor_exclusive_zone;
};
}
}

#endif /* MIR_SHELL_SURFACE_SPECIFICATION_H_ */
