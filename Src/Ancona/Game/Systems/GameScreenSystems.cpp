#include <Ancona/Game/Systems/GameScreenSystems.hpp>

using namespace ild;

GameScreenSystems::GameScreenSystems(
        sf::RenderWindow & window) :
    ScreenSystemsContainer()
{
    _physics = ConstructSystem<PlatformPhysicsSystem>("physics", *_systemManager);
    _input = new InputControlSystem(*_systemManager);
    _collision = new CollisionSystem(*_systemManager, *_physics);
    _camera = new CameraSystem(*_systemManager);
    _drawable = ConstructSystem<DrawableSystem>("drawable", window, *_systemManager);

    _physics->SetGravity(Point(0,10));
}
