#include <Ancona/Core/Game.hpp>
#include <Ancona/HAL/Joystick.hpp>

namespace ildhal
{

std::unordered_map<int, std::set<int>> Joystick::_pressedButtons;
std::unordered_map<int, std::set<int>> Joystick::_releasedButtons;
std::unordered_map<int, std::set<int>> Joystick::_heldButtons;
std::unordered_map<int, std::unordered_map<int, unsigned long>> Joystick::_heldButtonsToFrameCount;
std::unordered_map<int, std::set<int>> Joystick::_heldButtonsToClear;

bool Joystick::IsButtonPressed(const int joystick, const int button)
{
    return _pressedButtons.find(joystick) != _pressedButtons.end() &&
        _pressedButtons[joystick].find(button) != _pressedButtons[joystick].end();
}

bool Joystick::IsButtonReleased(const int joystick, const int button)
{
    return _releasedButtons.find(joystick) != _releasedButtons.end() &&
        _releasedButtons[joystick].find(button) != _releasedButtons[joystick].end();
}

bool Joystick::IsButtonDown(const int joystick, const int button)
{
    // TODO implement clearing _heldKeysToClear in _ClearButtons to uncomment actual impl
    return false;
    // return alg::contains(_heldButtons, joystick) && alg::contains(_heldButtons[joystick], button);
}

void Joystick::_AddButtonPress(const int joystick, const int button)
{
    if (_pressedButtons.find(joystick) == _pressedButtons.end())
    {
        _pressedButtons.insert({ joystick, std::set<int>() });
    }

    _pressedButtons[joystick].insert(button);

    if (_heldButtons.find(joystick) == _heldButtons.end())
    {
        _heldButtons.insert({ joystick, std::set<int>() });
    }

    _heldButtons[joystick].insert(button);

    if (_heldButtonsToFrameCount.find(joystick) == _heldButtonsToFrameCount.end())
    {
        _heldButtonsToFrameCount.insert({ joystick, std::unordered_map<int, unsigned long>() });
    }

    if (_heldButtonsToFrameCount[joystick].find(button) == _heldButtonsToFrameCount[joystick].end())
    {
        _heldButtonsToFrameCount[joystick].insert({ button, ild::Game::FrameCount });
    }
}

void Joystick::_AddButtonRelease(const int joystick, const int button)
{
    if (_releasedButtons.find(joystick) == _releasedButtons.end())
    {
        _releasedButtons.insert({ joystick, std::set<int>() });
    }

    if (_heldButtonsToFrameCount[joystick][button] != ild::Game::FrameCount)
    {
        auto iter = std::find(_heldButtons[joystick].begin(), _heldButtons[joystick].end(), button);
        if (iter != _heldButtons[joystick].end())
        {
            _heldButtons[joystick].erase(iter);
        }
    }
    else
    {
        if (_heldButtonsToClear.find(joystick) == _heldButtonsToClear.end())
        {
            _heldButtonsToClear.insert({ joystick, std::set<int>() });
        }

        _heldButtonsToClear[joystick].insert(button);
    }
}

void Joystick::_ClearButtons()
{
    _pressedButtons.clear();
    _releasedButtons.clear();

    // TODO implement clearing _heldKeysToClear
}

} // namespace ildhal
