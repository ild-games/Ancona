#include <Ancona/Core2D/InputDevices/Keyboard.hpp>

using namespace ild;

std::set<sf::Keyboard::Key> Keyboard::_pressedKeys;
std::set<sf::Keyboard::Key> Keyboard::_releasedKeys;

bool Keyboard::IsKeyPressed(const sf::Keyboard::Key & key)
{
    return _pressedKeys.find(key) != _pressedKeys.end();
}

bool Keyboard::IsKeyReleased(const sf::Keyboard::Key & key)
{
    return _releasedKeys.find(key) != _releasedKeys.end();
}

bool Keyboard::IsKeyDown(const sf::Keyboard::Key & key)
{
    return sf::Keyboard::isKeyPressed(key);
}

void Keyboard::_AddKeyPress(const sf::Keyboard::Key & key)
{
    _pressedKeys.insert(key);
}

void Keyboard::_AddKeyRelease(const sf::Keyboard::Key & key)
{
    _releasedKeys.insert(key);
}

void Keyboard::_ClearKeys() 
{
    _pressedKeys.clear();
    _releasedKeys.clear();
}
