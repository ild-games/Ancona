#include <Ancona/HAL/Touch.hpp>
#include <Ancona/Util/Algorithm.hpp>
#include <Ancona/Core2D/Core/Game.hpp>

namespace ildhal
{

std::set<unsigned int> Touch::_pressedFingers;
std::set<unsigned int> Touch::_releasedFingers;
std::set<unsigned int> Touch::_heldFingers;
std::map<unsigned int, unsigned int> Touch::_heldFingersToFrameCount;
std::set<unsigned int> Touch::_heldFingersToClear;
std::map<unsigned int, ild::Vector2i> Touch::_fingerPosition;

bool Touch::IsFingerPressed(unsigned int finger)
{
    return alg::contains(_pressedFingers, finger);
}

bool Touch::IsFingerReleased(unsigned int finger)
{
    return alg::contains(_releasedFingers, finger);
}

bool Touch::IsFingerDown(unsigned int finger)
{
    return alg::contains(_heldFingers, finger);
}

ild::Vector2i Touch::FingerPosition(unsigned int finger)
{
    if (_fingerPosition.find(finger) != _fingerPosition.end()) {
        return _fingerPosition[finger];
    }

    return ild::Vector2i(0, 0);
}

void Touch::_AddFingerPress(unsigned int finger, int x, int y)
{
    _pressedFingers.insert(finger);
    _heldFingers.insert(finger);
    _heldFingersToFrameCount[finger] = ild::Game::FrameCount;
    _fingerPosition[finger] = ild::Vector2i(x, y);
}

void Touch::_AddFingerRelease(unsigned int finger)
{
    _releasedFingers.insert(finger);
    if (_heldFingersToFrameCount[finger] != ild::Game::FrameCount) {
        auto iter = std::find(_heldFingers.begin(), _heldFingers.end(), finger);
        if (iter != _heldFingers.end()) {
            _heldFingers.erase(iter);
        }
        _fingerPosition[finger] = ild::Vector2i(0, 0);
    } else {
        _heldFingersToClear.insert(finger);
    }
}

void Touch::_AddFingerMoved(unsigned int finger, int x, int y)
{
    _fingerPosition[finger] = ild::Vector2i(x, y);
}

void Touch::_ClearFingers()
{
    _pressedFingers.clear();
    _releasedFingers.clear();
    for (auto heldFingerToClear : _heldFingersToClear) {
        _heldFingers.erase(std::find(_heldFingers.begin(), _heldFingers.end(), heldFingerToClear));
        _fingerPosition[heldFingerToClear] = ild::Vector2i(0, 0);
        _heldFingersToFrameCount[heldFingerToClear] = 0;
    }
    _heldFingersToClear.clear();
}

void Touch::_ClearAllFingersState()
{
    _pressedFingers.clear();
    _releasedFingers.clear();
    _heldFingers.clear();
    _heldFingersToClear.clear();
}

}
