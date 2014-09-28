#include <SFML/Window.hpp>

#include <Ancona/Game/Screen/TestScreen.hpp>

#include <Ancona/Engine/EntityFramework/SystemManager.hpp>
#include <Ancona/Engine/Core/Systems/PositionSystem.hpp>
#include <Ancona/Game/Systems/KeyboardPlayerSystem.hpp>

using namespace ild;

TestScreen::TestScreen(ScreenManager & manager)
    : AbstractScreen(manager)
{
    _systemManager = new SystemManager();
    _positionSystem = new PositionSystem(*_systemManager);
    _keyboardPlayerSystem = new KeyboardPlayerSystem(*_systemManager,*_positionSystem);
}

void TestScreen::Update(float delta)
{
    _systemManager->Update(delta,UpdateStep::Update);
}

void TestScreen::Draw()
{
    _manager.Window().clear(sf::Color::Green);
    _systemManager->Update(0,UpdateStep::Draw);
}
