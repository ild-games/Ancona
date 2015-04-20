#include <Mallard/GameLib/Systems/GameScreenSystems.hpp>

using namespace ild;

GameScreenSystems::GameScreenSystems(
        ScreenManager & screenManager,
        int profile) :
    ScreenSystemsContainer(screenManager, profile)
{
    _physics = ConstructSystem<PlatformPhysicsSystem>("physics", *_systemManager);
    _camera = ConstructSystem<CameraSystem>("camera", *_systemManager);
    _input = new InputControlSystem(*_systemManager);
    _collision = ConstructSystem<CollisionSystem>("collision", *_systemManager, *_physics);
    _drawable = ConstructSystem<DrawableSystem>("drawable", screenManager.Window, *_systemManager);

    _physics->gravity(Point(0, 10));
}
