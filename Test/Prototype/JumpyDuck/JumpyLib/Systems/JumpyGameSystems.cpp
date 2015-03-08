#include "JumpyGameSystems.hpp"

using namespace ild;

JumpyGameSystems::JumpyGameSystems(ScreenManager & screenManager) :
    ScreenSystemsContainer(screenManager)
{
    _physics = new PlatformPhysicsSystem("physics", *_systemManager);
    _input = new InputControlSystem(*_systemManager);
    _camera = ConstructSystem<CameraSystem>("camera", *_systemManager);
    _drawable = ConstructSystem<DrawableSystem>("drawable", screenManager.Window, *_systemManager);

    _collision = new CollisionSystem(*_systemManager,*_physics);

    _collision->CreateType();
    _physics->SetGravity(Point(0,200));
}
