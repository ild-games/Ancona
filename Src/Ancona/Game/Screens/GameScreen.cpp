#include <Ancona/Game/EntityFactories/EnvironmentFactory.hpp>
#include <Ancona/Game/EntityFactories/PlayerFactory.hpp>
#include <Ancona/Game/Screens/GameScreen.hpp>

using namespace ild;

GameScreen::GameScreen(ScreenManager & manager) :
        AbstractScreen(manager, "game")
{
    _gameSystems = new GameSystems(manager.Window, &_systems);
    _collisionTypes["player"] = _gameSystems->GetCollision().CreateType();
    _collisionTypes["ground"] = _gameSystems->GetCollision().CreateType();
}

void GameScreen::Init()
{
    _entities["screenCam"] = factories::CreateScreenCamera(
            *_gameSystems,
            _manager.Window.getView());
    _gameSystems->GetDrawable().SetDefaultCamera(_gameSystems->GetCamera()[_entities["screenCam"]]);
    _entities["player"] = factories::CreatePlayer(
            _gameSystems,
            _collisionTypes);
    _entities["ground"] = factories::CreateGround(
            *_gameSystems,
            _collisionTypes);

    _gameSystems->GetCamera()[_entities["screenCam"]]->
        SetFollow(_gameSystems->GetPhysics()[_entities["player"]]);
}

void GameScreen::Update(float delta)
{
    _gameSystems->GetManager().Update(delta, UpdateStep::Update);
    _gameSystems->GetManager().Update(delta, UpdateStep::Input);
}

void GameScreen::Draw(float delta)
{
    _manager.Window.clear(sf::Color::Blue);
    _gameSystems->GetManager().Update(delta, UpdateStep::Draw);
}

