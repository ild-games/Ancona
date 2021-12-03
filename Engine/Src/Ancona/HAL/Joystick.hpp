// Altered SFML Joystick.hpp for Ancona's HAL abstraction layer, combined with Ancona joystick state tracker

////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2018 Laurent Gomila (laurent@sfml-dev.org)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#ifndef Ancona_HAL_Joystick_H_
#define Ancona_HAL_Joystick_H_

#include <set>
#include <unordered_map>

namespace ildhal
{

class Joystick
{
  public:
    ////////////////////////////////////////////////////////////
    /// \brief Constants related to joysticks capabilities
    ///
    ////////////////////////////////////////////////////////////
    enum
    {
        Count = 8,        ///< Maximum number of supported joysticks
        ButtonCount = 32, ///< Maximum number of supported buttons
        AxisCount = 8     ///< Maximum number of supported axes
    };

    ////////////////////////////////////////////////////////////
    /// \brief Axes supported by joysticks
    ///
    ////////////////////////////////////////////////////////////
    enum Axis
    {
        X,    ///< The X axis
        Y,    ///< The Y axis
        Z,    ///< The Z axis
        R,    ///< The R axis
        U,    ///< The U axis
        V,    ///< The V axis
        PovX, ///< The X axis of the point-of-view hat
        PovY  ///< The Y axis of the point-of-view hat
    };

    static bool IsButtonPressed(const int joystick, const int button);
    static bool IsButtonReleased(const int joystick, const int button);
    static bool IsButtonDown(const int joystick, const int button);
    static void _AddButtonPress(const int joystick, const int button);
    static void _AddButtonRelease(const int joystick, const int button);
    static void _ClearButtons();

  private:
    static std::unordered_map<int, std::set<int>> _pressedButtons;
    static std::unordered_map<int, std::set<int>> _releasedButtons;
};

} // namespace ildhal

#endif
