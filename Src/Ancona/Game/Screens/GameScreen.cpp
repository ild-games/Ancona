#include <Ancona/Game/Screens/GameScreen.hpp>

using namespace ild;

GameScreen::GameScreen(
        ScreenManager & manager,
        int profile) :
    AbstractScreen("game", manager)
{
    _gameSystems = std::unique_ptr<GameScreenSystems>(
            new GameScreenSystems(manager, profile));
    _collisionTypes["player"] = _gameSystems->GetCollision().CreateType();
    _collisionTypes["ground"] = _gameSystems->GetCollision().CreateType();
}

void GameScreen::Init()
{
    _entities["player"] = factories::CreatePlayer(
            *_gameSystems,
            _collisionTypes);
    _entities["ground"] = factories::CreateGround(
            *_gameSystems,
            _collisionTypes);
}

void GameScreen::Update(float delta)
{
    _gameSystems->GetSystemManager().Update(delta, UpdateStep::Update);
    _gameSystems->GetSystemManager().Update(delta, UpdateStep::Input);
}

void GameScreen::Draw(float delta)
{
    _screenManager.Window.clear(sf::Color::Blue);
    _gameSystems->GetSystemManager().Update(delta, UpdateStep::Draw);
}
