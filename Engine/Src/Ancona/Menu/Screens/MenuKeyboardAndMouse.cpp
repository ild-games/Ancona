#include <Ancona/Core2D/InputDevices/Keyboard.hpp>
#include <Ancona/Core2D/InputDevices/Mouse.hpp>

#include "MenuGameSystems.hpp"
#include "MenuKeyboardAndMouse.hpp"

using namespace ildmenu;

void MenuKeyboardAndMouse::HandleInput(float delta)
{
    auto isPressed = ild::Mouse::IsButtonDown(sf::Mouse::Left);
    auto mousePosition = _systems->screenManager().Window.mapPixelToCoords(
        sf::Mouse::getPosition(_systems->screenManager().Window.getWindow()),
        _systems->drawable().defaultCamera()->view());
    _playerComponent->UpdatePointer(sf::Vector2f(mousePosition), isPressed);
}
