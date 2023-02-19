#include <Ancona/HAL/Joystick.hpp>
#include <Ancona/HAL/Keyboard.hpp>
#include <Ancona/HAL/Mouse.hpp>
#include <Ancona/HAL/SDL/EventImpl.hpp>
#include <Ancona/HAL/Sensor.hpp>

#include <Ancona/System/Log.hpp>

namespace ildhal
{

int priv::EventImpl::_sdlToAnconaKeycodeMap[SDL_NUM_SCANCODES];

bool priv::EventImpl::TranslateSdlToAncona(const SDL_Event & sdlEvent, ildhal::Event & event, bool isKeyRepeatEnabled)
{
    switch (sdlEvent.type)
    {
        case SDL_QUIT:
            event.type = ildhal::Event::Closed;
            return true;
        case SDL_WINDOWEVENT:
            return TranslateSdlWindowEventToAncona(sdlEvent.window, event);
        case SDL_KEYDOWN:
            event.type = ildhal::Event::KeyPressed;
            return TranslateSdlKeyboardEventToAncona(sdlEvent.key, event, isKeyRepeatEnabled);
        case SDL_KEYUP:
            event.type = ildhal::Event::KeyReleased;
            return TranslateSdlKeyboardEventToAncona(sdlEvent.key, event, isKeyRepeatEnabled);
        case SDL_MOUSEBUTTONDOWN:
            event.type = ildhal::Event::MouseButtonPressed;
            return TranslateSdlMouseButtonEventToAncona(sdlEvent.button, event);
        case SDL_MOUSEBUTTONUP:
            event.type = ildhal::Event::MouseButtonReleased;
            return TranslateSdlMouseButtonEventToAncona(sdlEvent.button, event);
        case SDL_FINGERDOWN:
            event.type = ildhal::Event::TouchBegan;
            return TranslateSdlFingerEventToAncona(sdlEvent.tfinger, event);
        case SDL_FINGERUP:
            event.type = ildhal::Event::TouchEnded;
            return TranslateSdlFingerEventToAncona(sdlEvent.tfinger, event);
        case SDL_FINGERMOTION:
            event.type = ildhal::Event::TouchMoved;
            return TranslateSdlFingerEventToAncona(sdlEvent.tfinger, event);
        case SDL_JOYBUTTONDOWN:
            event.type = ildhal::Event::JoystickButtonPressed;
            return TranslateSdlJoyButtonEventToAncona(sdlEvent.jbutton, event);
        case SDL_JOYBUTTONUP:
            event.type = ildhal::Event::JoystickButtonReleased;
            return TranslateSdlJoyButtonEventToAncona(sdlEvent.jbutton, event);
    }

    return false;
}

bool priv::EventImpl::TranslateSdlWindowEventToAncona(const SDL_WindowEvent & sdlWindowEvent, ildhal::Event & event)
{
    switch (sdlWindowEvent.event)
    {
        case SDL_WINDOWEVENT_CLOSE:
            event.type = ildhal::Event::Closed;
            return true;
        case SDL_WINDOWEVENT_FOCUS_LOST:
            event.type = ildhal::Event::LostFocus;
            return true;
        case SDL_WINDOWEVENT_FOCUS_GAINED:
            event.type = ildhal::Event::GainedFocus;
            return true;
    }

    return false;
}

bool priv::EventImpl::TranslateSdlKeyboardEventToAncona(
    const SDL_KeyboardEvent & sdlKeyboardEvent,
    ildhal::Event & event,
    bool isKeyRepeatEnabled)
{
    if ((!isKeyRepeatEnabled && sdlKeyboardEvent.repeat) || sdlKeyboardEvent.keysym.scancode >= SDL_NUM_SCANCODES)
    {
        return false;
    }

    event.key.code = (Keyboard::Key) _sdlToAnconaKeycodeMap[sdlKeyboardEvent.keysym.scancode];
    event.key.alt = !!(sdlKeyboardEvent.keysym.mod & KMOD_ALT);
    event.key.control = !!(sdlKeyboardEvent.keysym.mod & KMOD_CTRL);
    event.key.shift = !!(sdlKeyboardEvent.keysym.mod & KMOD_SHIFT);
    event.key.system = !!(sdlKeyboardEvent.keysym.mod & KMOD_GUI);
    return true;
}

bool priv::EventImpl::TranslateSdlMouseButtonEventToAncona(
    const SDL_MouseButtonEvent & sdlMouseButtonEvent,
    ildhal::Event & event)
{
    switch (sdlMouseButtonEvent.button)
    {
        case SDL_BUTTON_LEFT:
            event.mouseButton.button = Mouse::Button::Left;
            break;
        case SDL_BUTTON_RIGHT:
            event.mouseButton.button = Mouse::Button::Right;
            break;
        case SDL_BUTTON_MIDDLE:
            event.mouseButton.button = Mouse::Button::Middle;
            break;
        case SDL_BUTTON_X1:
            event.mouseButton.button = Mouse::Button::XButton1;
            break;
        case SDL_BUTTON_X2:
            event.mouseButton.button = Mouse::Button::XButton2;
            break;
    }

    event.mouseButton.x = sdlMouseButtonEvent.x;
    event.mouseButton.y = sdlMouseButtonEvent.y;
    return true;
}

bool priv::EventImpl::TranslateSdlFingerEventToAncona(
    const SDL_TouchFingerEvent & sdlTouchFingerEvent,
    ildhal::Event & event)
{
    event.touch.x = sdlTouchFingerEvent.x;
    event.touch.y = sdlTouchFingerEvent.y;
    event.touch.finger = sdlTouchFingerEvent.fingerId;
    return true;
}

bool priv::EventImpl::TranslateSdlJoyButtonEventToAncona(
    const SDL_JoyButtonEvent & sdlJoyButtonEvent,
    ildhal::Event & event)
{
    event.joystickButton.joystickId = sdlJoyButtonEvent.which;
    event.joystickButton.button = sdlJoyButtonEvent.button;
    return true;
}

void priv::EventImpl::PopulateSdlToAnconaKeycodeMap()
{
    for (int i = 0; i < SDL_NUM_SCANCODES; i++)
    {
        _sdlToAnconaKeycodeMap[i] = -1;
    }

    _sdlToAnconaKeycodeMap[SDL_SCANCODE_UNKNOWN] = Keyboard::Key::Unknown;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_A] = Keyboard::Key::A;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_B] = Keyboard::Key::B;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_C] = Keyboard::Key::C;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_D] = Keyboard::Key::D;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_E] = Keyboard::Key::E;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_F] = Keyboard::Key::F;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_G] = Keyboard::Key::G;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_H] = Keyboard::Key::H;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_I] = Keyboard::Key::I;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_J] = Keyboard::Key::J;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_K] = Keyboard::Key::K;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_L] = Keyboard::Key::L;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_M] = Keyboard::Key::M;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_N] = Keyboard::Key::N;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_O] = Keyboard::Key::O;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_P] = Keyboard::Key::P;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_Q] = Keyboard::Key::Q;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_R] = Keyboard::Key::R;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_S] = Keyboard::Key::S;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_T] = Keyboard::Key::T;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_U] = Keyboard::Key::U;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_V] = Keyboard::Key::V;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_W] = Keyboard::Key::W;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_X] = Keyboard::Key::X;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_Y] = Keyboard::Key::Y;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_Z] = Keyboard::Key::Z;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_0] = Keyboard::Key::Num0;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_1] = Keyboard::Key::Num1;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_2] = Keyboard::Key::Num2;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_3] = Keyboard::Key::Num3;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_4] = Keyboard::Key::Num4;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_5] = Keyboard::Key::Num5;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_6] = Keyboard::Key::Num6;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_7] = Keyboard::Key::Num7;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_8] = Keyboard::Key::Num8;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_9] = Keyboard::Key::Num9;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_ESCAPE] = Keyboard::Key::Escape;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_LCTRL] = Keyboard::Key::LControl;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_LSHIFT] = Keyboard::Key::LShift;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_LALT] = Keyboard::Key::LAlt;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_LGUI] = Keyboard::Key::LSystem;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_RCTRL] = Keyboard::Key::RControl;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_RSHIFT] = Keyboard::Key::RShift;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_RALT] = Keyboard::Key::RAlt;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_RGUI] = Keyboard::Key::RSystem;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_MENU] = Keyboard::Key::Menu;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_LEFTBRACKET] = Keyboard::Key::LBracket;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_RIGHTBRACKET] = Keyboard::Key::RBracket;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_SEMICOLON] = Keyboard::Key::Semicolon;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_COMMA] = Keyboard::Key::Comma;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_PERIOD] = Keyboard::Key::Period;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_APOSTROPHE] = Keyboard::Key::Quote;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_SLASH] = Keyboard::Key::Slash;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_BACKSLASH] = Keyboard::Key::Backslash;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_GRAVE] = Keyboard::Key::Tilde;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_EQUALS] = Keyboard::Key::Equal;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_MINUS] = Keyboard::Key::Hyphen;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_SPACE] = Keyboard::Key::Space;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_RETURN] = Keyboard::Key::Enter;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_BACKSPACE] = Keyboard::Key::Backspace;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_TAB] = Keyboard::Key::Tab;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_PAGEUP] = Keyboard::Key::PageUp;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_PAGEDOWN] = Keyboard::Key::PageDown;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_END] = Keyboard::Key::End;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_HOME] = Keyboard::Key::Home;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_INSERT] = Keyboard::Key::Insert;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_DELETE] = Keyboard::Key::Delete;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_KP_PLUS] = Keyboard::Key::Add;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_KP_MINUS] = Keyboard::Key::Subtract;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_KP_MULTIPLY] = Keyboard::Key::Multiply;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_KP_DIVIDE] = Keyboard::Key::Divide;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_LEFT] = Keyboard::Key::Left;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_RIGHT] = Keyboard::Key::Right;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_UP] = Keyboard::Key::Up;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_DOWN] = Keyboard::Key::Down;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_KP_0] = Keyboard::Key::Numpad0;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_KP_1] = Keyboard::Key::Numpad1;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_KP_2] = Keyboard::Key::Numpad2;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_KP_3] = Keyboard::Key::Numpad3;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_KP_4] = Keyboard::Key::Numpad4;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_KP_5] = Keyboard::Key::Numpad5;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_KP_6] = Keyboard::Key::Numpad6;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_KP_7] = Keyboard::Key::Numpad7;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_KP_8] = Keyboard::Key::Numpad8;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_KP_9] = Keyboard::Key::Numpad9;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_F1] = Keyboard::Key::F1;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_F2] = Keyboard::Key::F2;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_F3] = Keyboard::Key::F3;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_F4] = Keyboard::Key::F4;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_F5] = Keyboard::Key::F5;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_F6] = Keyboard::Key::F6;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_F7] = Keyboard::Key::F7;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_F8] = Keyboard::Key::F8;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_F9] = Keyboard::Key::F9;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_F10] = Keyboard::Key::F10;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_F11] = Keyboard::Key::F11;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_F12] = Keyboard::Key::F12;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_F13] = Keyboard::Key::F13;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_F14] = Keyboard::Key::F14;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_F15] = Keyboard::Key::F15;
    _sdlToAnconaKeycodeMap[SDL_SCANCODE_PAUSE] = Keyboard::Key::Pause;
}

} // namespace ildhal
