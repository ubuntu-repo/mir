/*
 * Copyright © 2015 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License version 3,
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by: Daniel van Vugt <daniel.van.vugt@canonical.com>
 */

#include "mir/plugin.h"

namespace mir
{

Plugin::Plugin()
{
}

Plugin::~Plugin()
{
    // Empty, but very important this implementation exists in one common
    // location and is not re-instantiated inside plugin libraries themselves.
}

void Plugin::hold_resource(std::shared_ptr<void> const& r)
{
    resources.push_back(r);
}

void Plugin::safely_unload(std::shared_ptr<Plugin>& plugin)
{
    if (plugin.use_count() == 0)
        throw new std::runtime_error("Can't safely unload a plugin that's "
                                     "not presently loaded.");
    if (plugin.use_count() > 1)
        throw new std::runtime_error("Can't safely unload a plugin that's "
                                     "still in use.");

    auto res = std::move(plugin->resources);
    plugin.reset(); // <- First destruct everything that came from the plugin.
    res.clear();    // <- Second unload the library, as we now know it's safe
                    //    and there are no destructors left in it to call.
}

} // namespace mir
