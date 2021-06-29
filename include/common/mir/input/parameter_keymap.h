/*
 * Copyright © 2016 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License version 2 or 3,
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
 * Authored by:
 *   Andreas Pokorny <andreas.pokorny@canonical.com>
 */

#ifndef MIR_INPUT_PARAMETER_KEYMAP_H_
#define MIR_INPUT_PARAMETER_KEYMAP_H_

#include "keymap.h"

#include <string>

namespace mir
{
namespace input
{

class ParameterKeymap
    : public Keymap
{
public:
    static auto constexpr default_model{"pc105+inet"};
    static auto constexpr default_layout{"us"};

    ParameterKeymap() = default;
    ParameterKeymap(std::string&& model, std::string&& layout, std::string&& variant, std::string&& options)
        : model_{model}, layout{layout}, variant{variant}, options{options}
    {
    }

    ParameterKeymap(
        std::string const& model,
        std::string const& layout,
        std::string const& variant,
        std::string const& options)
        : model_{model}, layout{layout}, variant{variant}, options{options}
    {
    }

    auto operator==(Keymap const& other) const -> bool override;
    auto model() const -> std::string override;
    auto make_unique_xkb_keymap(xkb_context* context) const -> XKBKeymapPtr override;

private:
    std::string model_{default_model};
    std::string layout{default_layout};
    std::string variant;
    std::string options;
};

}
}

#endif // MIR_INPUT_PARAMETER_KEYMAP_H_

