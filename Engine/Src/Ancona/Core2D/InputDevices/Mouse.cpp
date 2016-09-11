#include <Ancona/Core2D/InputDevices/Mouse.hpp>
#include <Ancona/Util/Algorithm/ContainerExtensions.hpp>

using namespace ild;

std::set<sf::Mouse::Button> Mouse::_pressedButtons;
std::set<sf::Mouse::Button> Mouse::_releasedButtons;

bool Mouse::IsButtonPressed(const sf::Mouse::Button &btn)
{
    return alg::contains(_pressedButtons, btn);
}

bool Mouse::IsButtonReleased(const sf::Mouse::Button &btn)
{
    return alg::contains(_releasedButtons, btn);
}

bool Mouse::IsButtonDown(const sf::Mouse::Button &btn)
{
    return sf::Mouse::isButtonPressed(btn);
}

void Mouse::_AddButtonPress(const sf::Mouse::Button &btn)
{
    _pressedButtons.insert(btn);
}

void Mouse::_AddButtonRelease(const sf::Mouse::Button &btn)
{
    _releasedButtons.insert(btn);
}

void Mouse::_ClearButtons()
{
    _pressedButtons.clear();
    _releasedButtons.clear();
}
