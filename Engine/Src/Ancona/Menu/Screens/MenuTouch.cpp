#include <sstream>
#include <limits>

#include <Ancona/HAL/Touch.hpp>
#include <Ancona/Menu/Screens/MenuGameSystems.hpp>
#include <Ancona/Menu/Screens/MenuTouch.hpp>

using namespace ildmenu;

void MenuTouch::HandleInput(float delta)
{
    HandleFingerPress(0, delta);
}

void MenuTouch::HandleFingerPress(const int finger, float delta)
{
    if (ildhal::Touch::IsFingerDown(finger))
    {
        using namespace ild;

        auto fingerPosition = _systems->screenManager().Window.MapPixelToCoords(
            ildhal::Touch::FingerPosition(finger),
            _systems->drawable().defaultCamera()->view());
        _lastPosition = sf::Vector2f(fingerPosition);
        _playerComponent->UpdatePointer(_lastPosition, true);
    }
    else if (ildhal::Touch::IsFingerReleased(finger))
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
    return ildhal::Touch::IsFingerDown(0) || ildhal::Touch::IsFingerDown(1);
}
