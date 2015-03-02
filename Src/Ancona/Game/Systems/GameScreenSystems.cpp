#include <Ancona/Game/Systems/GameScreenSystems.hpp>

using namespace ild;

GameScreenSystems::GameScreenSystems(ScreenManager & screenManager) :
    ScreenSystemsContainer(screenManager)
{
    _physics = ConstructSystem<PlatformPhysicsSystem>("physics", *_systemManager);
    _camera = ConstructSystem<CameraSystem>("camera", *_systemManager);
    _input = new InputControlSystem(*_systemManager);
    _collision = new CollisionSystem(*_systemManager, *_physics);
    _drawable = ConstructSystem<DrawableSystem>("drawable", screenManager.Window, *_systemManager);

    _physics->SetGravity(Point(0,10));
}
