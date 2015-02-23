#include <Ancona/Game/Systems/GameSystems.hpp>

using namespace ild;

GameSystems::GameSystems(sf::RenderWindow & window, SystemManager * manager)
{
    _manager = manager;
    _physics = new PlatformPhysicsSystem(*_manager);
    _input = new InputControlSystem(*_manager);
    _collision = new CollisionSystem(*_manager, *_physics);
    _camera = new CameraSystem(*_manager);
    _drawable = new DrawableSystem(
            window, 
            *_manager);

    _physics->SetGravity(Point(0,10));
}
