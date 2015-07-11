#include "TestScreen.hpp"

using namespace ild;

TestScreen::TestScreen(
        ScreenManager & manager,
        SpriteTilesheetInputHandler * inputHandler) :
    AbstractScreen("test-screen", manager),
    _inputHandler(inputHandler)
{
    _systems = std::unique_ptr<SpriteTilesheetGameSystems>(new SpriteTilesheetGameSystems(manager));
}

void TestScreen::Init()
{
}

void TestScreen::Update(float delta)
{
    _systems->systemManager().Update(delta, UpdateStep::Update);
    _systems->systemManager().Update(delta, UpdateStep::Input);
}

void TestScreen::Draw(float delta)
{
    _screenManager.Window.clear(sf::Color::Blue);
    _systems->systemManager().Update(delta, UpdateStep::Draw);
}
