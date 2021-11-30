#include <Ancona/HAL/Mouse.hpp>
#include <Ancona/HAL/Window.hpp>
#include <Ancona/HAL/SFML/WindowImpl.hpp>

#include <Ancona/Core2D/Core/Game.hpp>
#include <Ancona/Util/Algorithm.hpp>

namespace ildhal
{

std::set<Mouse::Button> Mouse::_pressedButtons;
std::set<Mouse::Button> Mouse::_releasedButtons;
std::set<Mouse::Button> Mouse::_heldButtons;
std::map<Mouse::Button, unsigned int> Mouse::_heldButtonsToFrameCount;
std::set<Mouse::Button> Mouse::_heldButtonsToClear;

ild::Vector2i Mouse::GetPosition()
{
    auto mousePosition = sf::Mouse::getPosition();
    return ild::Vector2i(mousePosition.x, mousePosition.y);
}

ild::Vector2i Mouse::GetPosition(const Window & relativeTo)
{
    auto & sfmlRenderWindow = relativeTo.windowImpl().sfmlRenderWindow();
    auto mousePosition = sf::Mouse::getPosition(sfmlRenderWindow);
    return ild::Vector2i(mousePosition.x, mousePosition.y);
}

bool Mouse::IsButtonPressed(const Mouse::Button & btn)
{
    return alg::contains(_pressedButtons, btn);
}

bool Mouse::IsButtonReleased(const Mouse::Button & btn)
{
    return alg::contains(_releasedButtons, btn);
}

bool Mouse::IsButtonDown(const Mouse::Button & btn)
{
    return alg::contains(_heldButtons, btn);
}

void Mouse::_AddButtonPress(const Mouse::Button & btn)
{
    _pressedButtons.insert(btn);
    _heldButtons.insert(btn);
    _heldButtonsToFrameCount[btn] = ild::Game::FrameCount;
}

void Mouse::_AddButtonRelease(const Mouse::Button & btn)
{
    _releasedButtons.insert(btn);
    if (_heldButtonsToFrameCount[btn] != ild::Game::FrameCount) {
        auto iter = std::find(_heldButtons.begin(), _heldButtons.end(), btn);
        if (iter != _heldButtons.end()) {
            _heldButtons.erase(iter);
        }
    } else {
        _heldButtonsToClear.insert(btn);
    }
}

void Mouse::_ClearButtons()
{
    _pressedButtons.clear();
    _releasedButtons.clear();
    for (auto heldButtonToClear : _heldButtonsToClear) {
        auto iter = std::find(_heldButtons.begin(), _heldButtons.end(), heldButtonToClear);
        if (iter != _heldButtons.end()) {
            _heldButtons.erase(iter);
        }
        _heldButtonsToFrameCount[heldButtonToClear] = 0;
    }
    _heldButtonsToClear.clear();
}

}
