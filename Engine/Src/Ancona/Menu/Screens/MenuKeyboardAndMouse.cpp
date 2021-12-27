#include <Ancona/HAL.hpp>
#include <Ancona/System/Log.hpp>

#include "MenuGameSystems.hpp"
#include "MenuKeyboardAndMouse.hpp"

namespace ild
{

void MenuKeyboardAndMouse::HandleInput(float delta)
{
    auto isPressed = ildhal::Mouse::IsButtonDown(ildhal::Mouse::Left);
    auto & window = _systems->screenManager().Window;
    auto mouseWindowPixelPosition = ildhal::Mouse::GetPosition(window);
    auto defaultView = _systems->drawable().defaultCamera()->view();
    auto mouseCoordsPosition = window.MapPixelToCoords(mouseWindowPixelPosition, defaultView);

    _playerComponent->UpdatePointer(mouseCoordsPosition, isPressed);
}

} // namespace ild
