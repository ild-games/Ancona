#include "ImpossibleGameSystems.hpp"

using namespace ild;

ImpossibleGameSystems::ImpossibleGameSystems(ScreenManager & screenManager) :
    ScreenSystemsContainer(screenManager, 0)
{
    _physics = ConstructSystem<PlatformPhysicsSystem>("physics", *_systemManager);
    _input = new InputControlSystem(*_systemManager);
    _camera = ConstructSystem<CameraSystem>("camera", *_systemManager);
    _drawable = ConstructSystem<DrawableSystem>("drawable", screenManager.Window, *_systemManager);
    _collision = ConstructSystem<CollisionSystem>("collision", *_systemManager,*_physics);
    _fadeDrawable = ConstructSystem<FadeDrawableSystem>("fadeDrawable", *_systemManager);

    _collision->CreateType("null-type");
    _collision->CreateType("player-type");
    _collision->CreateType("death-type");
    _collision->CreateType("ground-type");
    _collision->CreateType("ground-warp-type");
    _physics->gravity(Point(0, 1000));
}
