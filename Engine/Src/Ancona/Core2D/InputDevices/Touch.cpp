#include <Ancona/Core2D/InputDevices/Touch.hpp>
#include <Ancona/Util/Algorithm/ContainerExtensions.hpp>
#include <Ancona/Core2D/Core/Game.hpp>
#include <Ancona/System/Log.hpp>
#include <sstream>

using namespace ild;

std::set<unsigned int> Touch::_pressedFingers;
std::set<unsigned int> Touch::_releasedFingers;
std::set<unsigned int> Touch::_heldFingers;
std::map<unsigned int, unsigned int> Touch::_heldFingersToFrameCount;
std::set<unsigned int> Touch::_heldFingersToClear;
std::map<unsigned int, sf::Vector2i> Touch::_fingerPosition;

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

sf::Vector2i Touch::FingerPosition(unsigned int finger)
{
    if (_fingerPosition.find(finger) != _fingerPosition.end()) {
        return _fingerPosition[finger];
    }

    return sf::Vector2i(0, 0);
}

void Touch::_AddFingerPress(unsigned int finger, int x, int y)
{
    _pressedFingers.insert(finger);
    _heldFingers.insert(finger);
    _heldFingersToFrameCount[finger] = Game::FrameCount;
    _fingerPosition[finger] = sf::Vector2i(x, y);
}

void Touch::_AddFingerRelease(unsigned int finger)
{
    _releasedFingers.insert(finger);
    if (_heldFingersToFrameCount[finger] != Game::FrameCount) {
        _heldFingers.erase(std::find(_heldFingers.begin(), _heldFingers.end(), finger));
        _fingerPosition[finger] = sf::Vector2i(0, 0);
    } else {
        _heldFingersToClear.insert(finger);
    }
}

void Touch::_AddFingerMoved(unsigned int finger, int x, int y)
{
    _fingerPosition[finger] = sf::Vector2i(x, y);
}

void Touch::_ClearFingers()
{
    _pressedFingers.clear();
    _releasedFingers.clear();
    for (auto heldFingerToClear : _heldFingersToClear) {
        _heldFingers.erase(std::find(_heldFingers.begin(), _heldFingers.end(), heldFingerToClear));
        _fingerPosition[heldFingerToClear] = sf::Vector2i(0, 0);
        _heldFingersToFrameCount[heldFingerToClear] = 0;
    }
    _heldFingersToClear.clear();
}
