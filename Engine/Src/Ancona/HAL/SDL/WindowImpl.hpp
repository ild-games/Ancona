#pragma once

#include <memory>

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#include <Ancona/HAL/SDL/ClockImpl.hpp>
#include <Ancona/HAL/SDL/RenderTargetImpl.hpp>

namespace ildhal
{

namespace priv
{

struct SDL_WindowDestructor
{
    void operator()(SDL_Window * w) const
    {
        SDL_DestroyWindow(w);
        IMG_Quit();
        SDL_Quit();
    }
};

class WindowImpl : public RenderTargetImpl
{
  public:
    WindowImpl(SDL_Window *, SDL_Renderer *);

    /* getters and setters */
    SDL_Window & sdlWindow() const { return *_sdlWindow; }
    bool isClosed() const { return _isClosed; }
    void isClosed(bool newIsClosed) { _isClosed = newIsClosed; }
    bool isActive() const { return _isActive; }
    void isActive(bool newIsActive) { _isActive = newIsActive; }
    void keyRepeatEnabled(bool enabled) { _keyRepeatEnabled = enabled; }
    bool keyRepeatEnabled() const { return _keyRepeatEnabled; }
    void frameTimeLimit(const ildhal::Time & newFrameTimeLimit) { _frameTimeLimit = newFrameTimeLimit; }
    const ildhal::Time & frameTimeLimit() const { return _frameTimeLimit; }
    ildhal::Clock & clock() { return _clock; }

  private:
    std::unique_ptr<SDL_Window, SDL_WindowDestructor> _sdlWindow;

    bool _isClosed = false;
    bool _isActive = false;
    bool _keyRepeatEnabled = false;
    ildhal::Time _frameTimeLimit = ildhal::Time::Zero;
    ildhal::Clock _clock;
};

} // namespace priv

} // namespace ildhal
