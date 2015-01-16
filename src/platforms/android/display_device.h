/*
 * Copyright © 2013 Canonical Ltd.
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
 * Authored by: Kevin DuBois <kevin.dubois@canonical.com>
 */

#ifndef MIR_GRAPHICS_ANDROID_DISPLAY_SUPPORT_PROVIDER_H_
#define MIR_GRAPHICS_ANDROID_DISPLAY_SUPPORT_PROVIDER_H_

#include "mir/graphics/renderable.h"
#include "mir_toolkit/common.h"
#include "display_name.h"
#include <EGL/egl.h>

namespace mir
{
namespace graphics
{
class Buffer;
class Renderable;

namespace android
{
class RenderableListCompositor;
class SwappingGLContext;
class LayerList;

class DisplayDevice
{
public:
    virtual ~DisplayDevice() = default;

    /* \returns true if the DisplayDevice can support the renderlist
                false if the display device cannot support drawing the given renderlist.
    */
    virtual bool compatible_renderlist(RenderableList const& renderlist) = 0;

    /* post the list */
    virtual void commit(
        DisplayName,
        LayerList&,
        bool force_swap,
        SwappingGLContext const& context,
        RenderableListCompositor const& list_compositor) = 0;

    //notify the DisplayDevice that the screen content was cleared in a way other than the above fns
    virtual void content_cleared() = 0;

protected:
    DisplayDevice() = default;
    DisplayDevice& operator=(DisplayDevice const&) = delete;
    DisplayDevice(DisplayDevice const&) = delete;
};

}
}
}

#endif /* MIR_GRAPHICS_ANDROID_DISPLAY_SUPPORT_PROVIDER_H_ */
