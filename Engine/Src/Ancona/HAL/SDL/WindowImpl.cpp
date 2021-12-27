// Altered SFML Window.cpp for Ancona's HAL abstraction layer.
// Portions of the SFML Window.cpp code around framerate limiting
// were replicated in an SDL context here.

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

#include <Ancona/HAL/Keyboard.hpp>
#include <Ancona/HAL/Mouse.hpp>
#include <Ancona/HAL/SDL/EventImpl.hpp>
#include <Ancona/HAL/SDL/WindowImpl.hpp>
#include <Ancona/HAL/Sensor.hpp>
#include <Ancona/HAL/Sleep.hpp>
#include <Ancona/HAL/Window.hpp>
#include <Ancona/System/Log.hpp>
#include <Ancona/Util/Vector2.hpp>

namespace ildhal
{

/* Pimpl Implementation */

priv::WindowImpl::WindowImpl(SDL_Window * window, SDL_Renderer * renderer) :
        priv::RenderTargetImpl(renderer),
        _sdlWindow(std::unique_ptr<SDL_Window, SDL_WindowDestructor>(window))
{
}

/* HAL Interface Implementation */

Window::Window(const std::string & title, int width, int height, bool useVsync, unsigned int style)
{
    priv::EventImpl::PopulateSdlToAnconaKeycodeMap();

    // SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
    SDL_Init(SDL_INIT_EVERYTHING);

    uint32_t windowFlags = SDL_WINDOW_SHOWN;
    windowFlags |=
        ((style & ildhal::WindowStyle::Titlebar ? 0x0 : SDL_WINDOW_BORDERLESS) |
         (style & ildhal::WindowStyle::Resize ? SDL_WINDOW_RESIZABLE : 0x0) |
         (style & ildhal::WindowStyle::Close ? 0x0 : 0x0) |
         (style & ildhal::WindowStyle::Fullscreen ? SDL_WINDOW_FULLSCREEN : 0x0));
    SDL_Window * window =
        SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, windowFlags);

    uint32_t rendererFlags = ((useVsync ? SDL_RENDERER_PRESENTVSYNC : 0x0) | (SDL_RENDERER_ACCELERATED));
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, rendererFlags);
    SDL_RendererInfo rendererInfo;
    if (SDL_GetRendererInfo(renderer, &rendererInfo) == 0)
    {
        ILD_Log("Renderer name: " << std::string(rendererInfo.name));
    }

    _pimpl = std::make_unique<priv::WindowImpl>(window, renderer);
}

bool Window::PollEvent(Event & event)
{
    SDL_Event sdlEvent;
    if (!SDL_PollEvent(&sdlEvent))
    {
        return false;
    }

    return priv::EventImpl::TranslateSdlToAncona(sdlEvent, event, windowImpl().keyRepeatEnabled());
}

void Window::Display()
{
    SDL_RenderPresent(&windowImpl().sdlRenderer());

    const Time & frameTimeLimit = windowImpl().frameTimeLimit();
    Clock & clock = windowImpl().clock();
    if (frameTimeLimit != Time::Zero)
    {
        sleep(frameTimeLimit - clock.ElapsedTime());
        clock.Restart();
    }
}

void Window::Close()
{
    windowImpl().isClosed(true);
}

/* getters and setters */

ild::Vector2u Window::size() const
{
    int x = 0;
    int y = 0;
    SDL_GetWindowSize(&windowImpl().sdlWindow(), &x, &y);
    return ild::Vector2u((unsigned int) x, (unsigned int) y);
}

void Window::title(const std::string & title)
{
    SDL_SetWindowTitle(&windowImpl().sdlWindow(), title.c_str());
}

void Window::active(bool newActive)
{
    windowImpl().isActive(newActive);
}

bool Window::active() const
{
    return windowImpl().isActive();
}

bool Window::open() const
{
    return !windowImpl().isClosed();
}

void Window::keyRepeatEnabled(bool enabled)
{
    windowImpl().keyRepeatEnabled(enabled);
}

void Window::framerateLimit(unsigned int limit)
{
    if (limit > 0)
    {
        windowImpl().frameTimeLimit(seconds(1.0 / static_cast<double>(limit)));
    }
    else
    {
        windowImpl().frameTimeLimit(Time::Zero);
    }
}

priv::WindowImpl & Window::windowImpl() const
{
    return static_cast<priv::WindowImpl &>(*_pimpl);
}

} // namespace ildhal
