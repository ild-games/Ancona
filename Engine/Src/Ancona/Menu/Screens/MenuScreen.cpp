#include "MenuScreen.hpp"

#include <Ancona/Util/StrUtil.hpp>

using namespace ildmenu;

MenuScreen::MenuScreen(
        ButtonPressedCallback buttonPressed,
        std::string mapKey,
        ild::ScreenManager & manager,
        std::shared_ptr<MenuInputHandler> inputHandler) :
    ild::AbstractScreen(mapKey, manager),
    _buttonPressed(buttonPressed),
    _inputHandler(inputHandler)
{
    _systems = std::unique_ptr<MenuGameSystems>(new MenuGameSystems(manager));
}

void MenuScreen::Init()
{
    using namespace ild;
    _inputHandler->systems(_systems.get());

    auto inputEntity = _systems->systemManager().CreateEntity();
    auto menuInputComponent = new MenuInputComponent(*_systems, _inputHandler);

    _inputHandler->RegisterInputComponent(menuInputComponent);

    _systems->input().AddComponent(inputEntity, menuInputComponent);
}

void MenuScreen::Update(float delta)
{
    _systems->systemManager().Update(delta, ild::UpdateStep::Input);
    _systems->systemManager().Update(delta, ild::UpdateStep::Update);
    _systems->systemManager().Update(delta, ild::UpdateStep::Physics);

    if (_systems->button().WasEntityPressed())
    {
        _buttonPressed(_systems->button().GetPressedKey());
    }
}

void MenuScreen::Draw(float delta)
{
    _screenManager.Window.clear(sf::Color::Red);
    _systems->systemManager().Update(delta, ild::UpdateStep::Draw);
}
