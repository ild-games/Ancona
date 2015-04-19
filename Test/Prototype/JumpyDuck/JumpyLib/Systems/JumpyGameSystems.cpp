#include "JumpyGameSystems.hpp"

using namespace ild;

JumpyGameSystems::JumpyGameSystems(ScreenManager & screenManager) :
    ScreenSystemsContainer(screenManager, 1)
{
    _physics = ConstructSystem<PlatformPhysicsSystem>("physics", *_systemManager);
    _input = new InputControlSystem(*_systemManager);
    _camera = ConstructSystem<CameraSystem>("camera", *_systemManager);
    _drawable = ConstructSystem<DrawableSystem>("drawable", screenManager.Window, *_systemManager);
    _collision = ConstructSystem<CollisionSystem>("collision", *_systemManager,*_physics);
    _fadeDrawable = ConstructSystem<FadeDrawableSystem>("fadeDrawable", *_systemManager);

    _collision->CreateType("null-type");
    _physics->SetGravity(Point(0,200));
}
