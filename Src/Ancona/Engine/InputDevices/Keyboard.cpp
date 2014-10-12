#include <Ancona/Engine/InputDevices/Keyboard.hpp>

using namespace ild;

std::set<sf::Keyboard::Key> Keyboard::_pressedKeys;
std::set<sf::Keyboard::Key> Keyboard::_releasedKeys;

bool Keyboard::IsKeyPressed(const sf::Keyboard::Key & key)
{
    return Keyboard::_pressedKeys.find(key) != 
        Keyboard::_pressedKeys.end();
}

bool Keyboard::IsKeyReleased(const sf::Keyboard::Key & key)
{
    return Keyboard::_releasedKeys.find(key) != 
        Keyboard::_releasedKeys.end();
}

bool Keyboard::IsKeyDown(const sf::Keyboard::Key & key)
{
    return sf::Keyboard::isKeyPressed(key);
}

void Keyboard::_AddKeyPress(const sf::Keyboard::Key & key)
{
    Keyboard::_pressedKeys.insert(key);
}

void Keyboard::_AddKeyRelease(const sf::Keyboard::Key & key)
{
    Keyboard::_releasedKeys.insert(key);
}

void Keyboard::_ClearKeys() 
{
    Keyboard::_pressedKeys.clear();
    Keyboard::_releasedKeys.clear();
}
