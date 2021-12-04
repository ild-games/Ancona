// Altered SFML Mouse.hpp for Ancona's HAL abstraction layer, combined with Ancona mouse state tracker

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

#ifndef Ancona_HAL_Mouse_H_
#define Ancona_HAL_Mouse_H_

#include <map>
#include <set>
#include <unordered_map>

#include <Ancona/Util/Vector2.hpp>

namespace ildhal
{

class Window;

class Mouse
{
  public:
    enum Button
    {
        Left,     ///< The left mouse button
        Right,    ///< The right mouse button
        Middle,   ///< The middle (wheel) mouse button
        XButton1, ///< The first extra mouse button
        XButton2, ///< The second extra mouse button

        ButtonCount ///< Keep last -- the total number of mouse buttons
    };

    ////////////////////////////////////////////////////////////
    /// \brief Mouse wheels
    ///
    ////////////////////////////////////////////////////////////
    enum Wheel
    {
        VerticalWheel,  ///< The vertical mouse wheel
        HorizontalWheel ///< The horizontal mouse wheel
    };

    ////////////////////////////////////////////////////////////
    /// \brief Get the current position of the mouse in desktop coordinates
    ///
    /// This function returns the global position of the mouse
    /// cursor on the desktop.
    ///
    /// \return Current position of the mouse
    ///
    ////////////////////////////////////////////////////////////
    static ild::Vector2i GetPosition();

    ////////////////////////////////////////////////////////////
    /// \brief Get the current position of the mouse in window coordinates
    ///
    /// This function returns the current position of the mouse
    /// cursor, relative to the given window.
    ///
    /// \param relativeTo Reference window
    ///
    /// \return Current position of the mouse
    ///
    ////////////////////////////////////////////////////////////
    static ild::Vector2i GetPosition(const Window &relativeTo);

    /**
     * @brief Deteremines if a button was just pressed
     *
     * @param  btn Mouse::Button to check if it is pressed
     *
     * @return true if the button is pressed, otherwise false
     */
    static bool IsButtonPressed(const Mouse::Button &btn);

    /**
     * @brief Deteremines if a button was just released
     *
     * @param  btn Mouse::Button to check if it is released
     *
     * @return true if the button is released, otherwise false
     */
    static bool IsButtonReleased(const Mouse::Button &btn);

    /**
     * @brief Deteremines if a button is down
     *
     * @param  btn Mouse::Button to check if it is down
     *
     * @return true if the button is down, otherwise false
     */
    static bool IsButtonDown(const Mouse::Button &btn);

    /**
     * @brief INTERNAL ONLY
     *        Adds a button press event for the given button
     *
     * @param btn Mouse::Button being pressed
     */
    static void _AddButtonPress(const Mouse::Button &btn);

    /**
     * @brief INTERNAL ONLY
     *        Adds a button released event for the given button
     *
     * @param btn Mouse::Button being released
     */
    static void _AddButtonRelease(const Mouse::Button &btn);

    /**
     * @brief INTERNAL ONLY
     *        Clears all button events
     */
    static void _ClearButtons();

  private:
    static std::set<Mouse::Button> _pressedButtons;
    static std::set<Mouse::Button> _releasedButtons;
    static std::set<Mouse::Button> _heldButtons;
    static std::map<Mouse::Button, unsigned long> _heldButtonsToFrameCount;
    static std::set<Mouse::Button> _heldButtonsToClear;
};

} // namespace ildhal

#endif
