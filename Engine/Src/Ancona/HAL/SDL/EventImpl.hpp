#pragma once

#include <SDL2/SDL.h>

#include <Ancona/HAL/Event.hpp>

namespace ildhal
{

namespace priv
{

class EventImpl
{
  public:
    static void PopulateSdlToAnconaKeycodeMap();
    static bool TranslateSdlToAncona(const SDL_Event & sdlEvent, ildhal::Event & event, bool isKeyRepeatEnabled);

  private:
    static bool TranslateSdlWindowEventToAncona(const SDL_WindowEvent & sdlWindowEvent, ildhal::Event & event);
    static bool TranslateSdlKeyboardEventToAncona(
        const SDL_KeyboardEvent & sdlKeyboardEvent,
        ildhal::Event & event,
        bool isKeyRepeatEnabled);
    static bool TranslateSdlMouseButtonEventToAncona(
        const SDL_MouseButtonEvent & sdlMouseButtonEvent,
        ildhal::Event & event);
    static bool TranslateSdlFingerEventToAncona(
        const SDL_TouchFingerEvent & sdlTouchFingerEvent,
        ildhal::Event & event);
    static bool TranslateSdlJoyButtonEventToAncona(const SDL_JoyButtonEvent & sdlJoyButtonEvent, ildhal::Event & event);

    static int _sdlToAnconaKeycodeMap[SDL_NUM_SCANCODES];
};

} // namespace priv

} // namespace ildhal
