#include "JumpyGameSystems.hpp"

using namespace ild;

JumpyGameSystems::JumpyGameSystems(sf::RenderWindow & window)
{
    _manager = new SystemManager();
    _physics = new PlatformPhysicsSystem(*_manager);
    _input = new InputControlSystem(*_manager);
    _drawable = new DrawableSystem(
            window,
            *_manager);
}
