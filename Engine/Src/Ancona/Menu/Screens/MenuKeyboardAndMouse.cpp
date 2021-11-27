#include <Ancona/HAL/Mouse.hpp>

#include "MenuGameSystems.hpp"
#include "MenuKeyboardAndMouse.hpp"

using namespace ildmenu;

void MenuKeyboardAndMouse::HandleInput(float delta)
{
    auto isPressed = ildhal::Mouse::IsButtonDown(ildhal::Mouse::Left);
    auto & window = _systems->screenManager().Window;
    auto mouseWindowPixelPosition = ildhal::Mouse::GetPosition(window);
    auto defaultView = _systems->drawable().defaultCamera()->view();
    auto mouseCoordsPosition = window.MapPixelToCoords(mouseWindowPixelPosition, defaultView);

    _playerComponent->UpdatePointer(mouseCoordsPosition, isPressed);
}
