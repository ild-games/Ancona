#include "MenuGameSystems.hpp"

using namespace ildmenu;

MenuGameSystems::MenuGameSystems(ild::ScreenManager & screenManager) :
    ScreenSystemsContainer(screenManager, 0)
{
    _position = ConstructSystem<ild::PositionSystem>("position", *_systemManager);
    _input = new ild::InputControlSystem(*_systemManager);
    _camera = ConstructSystem<ild::CameraSystem>("camera", *_systemManager);
    _drawable = ConstructSystem<ild::DrawableSystem>("drawable", screenManager.Window, *_systemManager);
    _collision = ConstructSystem<ild::CollisionSystem>("collision", *_systemManager, *_position);
    _action = ConstructSystem<ild::ActionSystem>("action", *_systemManager, _position);
    _button = ConstructSystem<ButtonSystem>("button", *_systemManager);
}
