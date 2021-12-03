#include <SFML/Window.hpp>

#include <Ancona/HAL/Joystick.hpp>

namespace ildhal
{

std::unordered_map<int, std::set<int>> Joystick::_pressedButtons;
std::unordered_map<int, std::set<int>> Joystick::_releasedButtons;

bool Joystick::IsButtonPressed(const int joystick, const int button)
{
    return (
        _pressedButtons.find(joystick) != _pressedButtons.end() &&
        _pressedButtons[joystick].find(button) != _pressedButtons[joystick].end()
    );
}

bool Joystick::IsButtonReleased(const int joystick, const int button)
{
    return (
        _releasedButtons.find(joystick) != _releasedButtons.end() &&
        _releasedButtons[joystick].find(button) != _releasedButtons[joystick].end()
    );
}

bool Joystick::IsButtonDown(const int joystick, const int button)
{
    return sf::Joystick::isButtonPressed(joystick, button);
}

void Joystick::_AddButtonPress(const int joystick, const int button)
{
    if (_pressedButtons.find(joystick) == _pressedButtons.end()) {
        _pressedButtons.insert({joystick, std::set<int>()});
    }

    _pressedButtons[joystick].insert(button);
}

void Joystick::_AddButtonRelease(const int joystick, const int button)
{
    if (_releasedButtons.find(joystick) == _releasedButtons.end()) {
        _releasedButtons.insert({joystick, std::set<int>()});
    }

    _releasedButtons[joystick].insert(button);
}

void Joystick::_ClearButtons() 
{
    _pressedButtons.clear();
    _releasedButtons.clear();
}

}
