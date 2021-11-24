#include <sstream>
#include <limits>

#include <Ancona/Core2D/InputDevices/Touch.hpp>

#include "MenuGameSystems.hpp"
#include "MenuTouch.hpp"

using namespace ildmenu;

void MenuTouch::HandleInput(float delta)
{
    HandleFingerPress(0, delta);
}

void MenuTouch::HandleFingerPress(const int finger, float delta)
{
    if (ild::Touch::IsFingerDown(finger))
    {
        using namespace ild;

        auto fingerPosition = _systems->screenManager().Window.mapPixelToCoords(
            ild::Touch::FingerPosition(finger),
            _systems->drawable().defaultCamera()->view());
        _lastPosition = sf::Vector2f(fingerPosition);
        _playerComponent->UpdatePointer(_lastPosition, true);
    }
    else if (ild::Touch::IsFingerReleased(finger))
    {
        _playerComponent->UpdatePointer(_lastPosition, false);
    }
    else
    {
        auto infinity = std::numeric_limits<float>::infinity();
        _playerComponent->UpdatePointer(sf::Vector2f(infinity, infinity), false);
    }
}

bool MenuTouch::IsAnyFingerDown()
{
    return ild::Touch::IsFingerDown(0) || ild::Touch::IsFingerDown(1);
}
