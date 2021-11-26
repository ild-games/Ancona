////////////////////////////////////////////////////////////
// Altered SFML Window.hpp for abstraction layer
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

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <Ancona/HAL/Event.hpp>

namespace ildhal
{

namespace WindowStyle
{
    enum
    {
        None       = 0,
        Titlebar   = 1 << 0,
        Resize     = 1 << 1,
        Close      = 1 << 2,
        Fullscreen = 1 << 3,

        Default = Titlebar | Resize | Close
    };
}

class Window
{
    public:
        Window(
            const std::string& title,
            int width,
            int height,
            unsigned int style = WindowStyle::Default);

        ~Window();

        void setFramerateLimit(unsigned int limit);
        void setVerticalSyncEnabled(bool enabled);
        void setKeyRepeatEnabled(bool enabled);
        bool isOpen() const;
        bool pollEvent(Event & event);
        void clear(const sf::Color& color = sf::Color(0, 0, 0, 255));
        void display();
        void close();
        bool setActive(bool active = true) const;
        void resetGLStates();
        void draw(const sf::Drawable & drawable, const sf::RenderStates & states = sf::RenderStates::Default);
        void setView(const sf::View & view);
        const sf::View& getDefaultView() const;
        sf::Vector2f mapPixelToCoords(const sf::Vector2i& point, const sf::View & view) const;
        sf::Vector2u getSize() const;
        sf::RenderTarget & getRenderTarget();
        sf::Window & getWindow();

    private:
        class Impl;

        std::unique_ptr<Impl> _pimpl;
};

}

#endif
