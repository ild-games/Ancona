#include <Ancona/Core2D/InputDevices/Touch.hpp>
#include <Ancona/Util/Algorithm/ContainerExtensions.hpp>

using namespace ild;

std::set<unsigned int> Touch::_pressedFingers;
std::set<unsigned int> Touch::_releasedFingers;

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
    return sf::Touch::isDown(finger);
}

void Touch::_AddFingerPress(unsigned int finger)
{
    _pressedFingers.insert(finger);
}

void Touch::_AddFingerRelease(unsigned int finger)
{
    _releasedFingers.insert(finger);
}

void Touch::_ClearFingers()
{
    _pressedFingers.clear();
    _releasedFingers.clear();
}
