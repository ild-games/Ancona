#include <Ancona/Core/Game.hpp>
#include <Ancona/HAL/Touch.hpp>
#include <Ancona/System/Log.hpp>
#include <Ancona/Util/Algorithm.hpp>

namespace ildhal
{

std::set<int64_t> Touch::_pressedFingers;
std::set<int64_t> Touch::_releasedFingers;
std::set<int64_t> Touch::_heldFingers;
std::map<int64_t, unsigned long> Touch::_heldFingersToFrameCount;
std::set<int64_t> Touch::_heldFingersToClear;
std::map<int64_t, ild::Vector2i> Touch::_fingerPosition;

bool Touch::IsFingerPressed(int64_t finger)
{
    return alg::contains(_pressedFingers, finger);
}

bool Touch::IsFingerReleased(int64_t finger)
{
    return alg::contains(_releasedFingers, finger);
}

bool Touch::IsFingerDown(int64_t finger)
{
    return alg::contains(_heldFingers, finger);
}

ild::Vector2i Touch::FingerPosition(int64_t finger)
{
    if (_fingerPosition.find(finger) != _fingerPosition.end())
    {
        return _fingerPosition[finger];
    }

    return ild::Vector2i(0, 0);
}

void Touch::_AddFingerPress(int64_t finger, float x, float y, const ild::Vector2u & screenSize)
{
    _pressedFingers.insert(finger);
    _heldFingers.insert(finger);
    _heldFingersToFrameCount[finger] = ild::Game::FrameCount;
    _fingerPosition[finger] = ild::Vector2i(
        (int)(x * screenSize.x),
        (int)(y * screenSize.y));
}

void Touch::_AddFingerRelease(int64_t finger)
{
    _releasedFingers.insert(finger);
    if (_heldFingersToFrameCount[finger] != ild::Game::FrameCount)
    {
        auto iter = std::find(_heldFingers.begin(), _heldFingers.end(), finger);
        if (iter != _heldFingers.end())
        {
            _heldFingers.erase(iter);
        }
        _fingerPosition[finger] = ild::Vector2i(0, 0);
    }
    else
    {
        _heldFingersToClear.insert(finger);
    }
}

void Touch::_AddFingerMoved(int64_t finger, float x, float y, const ild::Vector2u & screenSize)
{
    _fingerPosition[finger] = ild::Vector2i(
        (int)(x * screenSize.x),
        (int)(y * screenSize.y));
}

void Touch::_ClearFingers()
{
    _pressedFingers.clear();
    _releasedFingers.clear();
    for (auto heldFingerToClear : _heldFingersToClear)
    {
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

} // namespace ildhal
