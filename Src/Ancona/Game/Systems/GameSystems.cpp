#include <Ancona/Game/Systems/GameSystems.hpp>

using namespace ild;

GameSystems::GameSystems(sf::RenderWindow & window)
{
    _manager = new SystemManager();
    _physics = new PlatformPhysicsSystem(*_manager);
    _drawable = new DrawableSystem(window, *_manager);
    _input = new InputControlSystem(*_manager);
    _collision = new CollisionSystem(*_manager, *_physics);
    _camera = new CameraSystem(*_manager);

    _physics->SetGravity(Point(0,10));
}
