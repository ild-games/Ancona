#include "JumpyGameSystems.hpp"

using namespace ild;

JumpyGameSystems::JumpyGameSystems(sf::RenderWindow & window)
{
    _manager = new SystemManager();
    _physics = new PlatformPhysicsSystem(*_manager);
    _input = new InputControlSystem(*_manager);
    _camera = new CameraSystem(*_manager);
    _drawable = new DrawableSystem(
            window,
            *_manager);
    _collision = new CollisionSystem(*_manager,*_physics);

    _collision->CreateType();
    _physics->SetGravity(Point(0,10));
}
