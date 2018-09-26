#include <Ancona/Core2D/InputDevices/Keyboard.hpp>
#include <Ancona/Util/Algorithm.hpp>
#include <Ancona/System/Log.hpp>
#include <Ancona/Core2D/Core/Game.hpp>

using namespace ild;

std::set<sf::Keyboard::Key> Keyboard::_pressedKeys;
std::set<sf::Keyboard::Key> Keyboard::_releasedKeys;
std::set<sf::Keyboard::Key> Keyboard::_heldKeys;
std::map<sf::Keyboard::Key, unsigned int> Keyboard::_heldKeysToFrameCount;
std::set<sf::Keyboard::Key> Keyboard::_heldKeysToClear;

bool Keyboard::IsKeyPressed(const sf::Keyboard::Key & key)
{
    return alg::contains(_pressedKeys, key);
}

bool Keyboard::IsKeyReleased(const sf::Keyboard::Key & key)
{
    return alg::contains(_releasedKeys, key);
}

bool Keyboard::IsKeyDown(const sf::Keyboard::Key & key)
{
    return alg::contains(_heldKeys, key);
}

void Keyboard::_AddKeyPress(const sf::Keyboard::Key & key)
{
    _pressedKeys.insert(key);
    _heldKeys.insert(key);
    _heldKeysToFrameCount[key] = Game::FrameCount;
}

void Keyboard::_AddKeyRelease(const sf::Keyboard::Key & key)
{
    _releasedKeys.insert(key);
    if (_heldKeysToFrameCount[key] != Game::FrameCount) {
        _heldKeys.erase(std::find(_heldKeys.begin(), _heldKeys.end(), key));
    } else {
        _heldKeysToClear.insert(key);
    }
}

void Keyboard::_ClearKeys() 
{
    _pressedKeys.clear();
    _releasedKeys.clear();
    for (auto heldKeyToClear : _heldKeysToClear) {
        _heldKeys.erase(std::find(_heldKeys.begin(), _heldKeys.end(), heldKeyToClear));
        _heldKeysToFrameCount[heldKeyToClear] = 0;
    }
    _heldKeysToClear.clear();
}
