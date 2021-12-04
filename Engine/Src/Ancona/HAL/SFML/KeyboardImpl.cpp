#include <Ancona/HAL/Keyboard.hpp>

#include <Ancona/Core2D/Core/Game.hpp>
#include <Ancona/Util/Algorithm.hpp>

namespace ildhal
{

std::set<Keyboard::Key> Keyboard::_pressedKeys;
std::set<Keyboard::Key> Keyboard::_releasedKeys;
std::set<Keyboard::Key> Keyboard::_heldKeys;
std::map<Keyboard::Key, unsigned long> Keyboard::_heldKeysToFrameCount;
std::set<Keyboard::Key> Keyboard::_heldKeysToClear;

bool Keyboard::IsKeyPressed(const Keyboard::Key &key)
{
    return alg::contains(_pressedKeys, key);
}

bool Keyboard::IsKeyReleased(const Keyboard::Key &key)
{
    return alg::contains(_releasedKeys, key);
}

bool Keyboard::IsKeyDown(const Keyboard::Key &key)
{
    return alg::contains(_heldKeys, key);
}

void Keyboard::_AddKeyPress(const Keyboard::Key &key)
{
    _pressedKeys.insert(key);
    _heldKeys.insert(key);
    _heldKeysToFrameCount[key] = ild::Game::FrameCount;
}

void Keyboard::_AddKeyRelease(const Keyboard::Key &key)
{
    _releasedKeys.insert(key);
    if (_heldKeysToFrameCount[key] != ild::Game::FrameCount)
    {
        auto iter = std::find(_heldKeys.begin(), _heldKeys.end(), key);
        if (iter != _heldKeys.end())
        {
            _heldKeys.erase(iter);
        }
    }
    else
    {
        _heldKeysToClear.insert(key);
    }
}

void Keyboard::_ClearKeys()
{
    _pressedKeys.clear();
    _releasedKeys.clear();
    for (auto heldKeyToClear : _heldKeysToClear)
    {
        auto iter = std::find(_heldKeys.begin(), _heldKeys.end(), heldKeyToClear);
        if (iter != _heldKeys.end())
        {
            _heldKeys.erase(iter);
        }
        _heldKeysToFrameCount[heldKeyToClear] = 0;
    }
    _heldKeysToClear.clear();
}

} // namespace ildhal
