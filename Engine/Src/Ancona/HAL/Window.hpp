// Altered SFML RenderWindow.hpp, Window.hpp, and WindowStyle.hpp for Ancona's HAL abstraction layer

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

#ifndef Ancona_HAL_Window_H_
#define Ancona_HAL_Window_H_

#include <Ancona/HAL/Event.hpp>
#include <Ancona/HAL/RenderTarget.hpp>

namespace ildhal
{

namespace WindowStyle
{
////////////////////////////////////////////////////////////
/// \brief Enumeration of the window styles
///
////////////////////////////////////////////////////////////
enum
{
    None = 0,            ///< No border / title bar (this flag and all others are mutually exclusive)
    Titlebar = 1 << 0,   ///< Title bar + fixed border
    Resize = 1 << 1,     ///< Title bar + resizable border + maximize button
    Close = 1 << 2,      ///< Title bar + close button
    Fullscreen = 1 << 3, ///< Fullscreen mode (this flag and all others are mutually exclusive)

    Default = Titlebar | Resize | Close ///< Default window style
};
} // namespace WindowStyle

namespace priv
{
class WindowImpl;
}

class Window : public RenderTarget
{
  public:
    Window(const std::string &title, int width, int height, unsigned int style = WindowStyle::Default);

    bool PollEvent(Event &event);
    void Display();
    void Close();

    /* getters and setters */
    virtual ild::Vector2u size() const;
    void title(const std::string &title);
    bool active(bool active = true) const;
    bool open() const;
    void keyRepeatEnabled(bool enabled);
    void verticalSyncEnabled(bool enabled);
    void framerateLimit(unsigned int limit);

    priv::WindowImpl &windowImpl() const;
};

} // namespace ildhal

#endif
