#include <Ancona/Game/Screens/GameScreen.hpp>

#include <Ancona/Game/EntityFactories/PlayerFactory.hpp>
#include <Ancona/Game/EntityFactories/EnvironmentFactory.hpp>
#include <SFML/Window.hpp>

using namespace ild;

GameScreen::GameScreen(ScreenManager & manager)
    : AbstractScreen(manager)
{
    _systems = new GameSystems(manager.Window);
    _collisionTypes["player"] = _systems->GetCollision().CreateType();
    _collisionTypes["ground"] = _systems->GetCollision().CreateType();
}

void GameScreen::Init()
{
    _entities["screenCam"] = factories::CreateScreenCamera(
            *_systems,
            _manager.Window.getView());
    _entities["player"] = factories::CreatePlayer(
            _systems,
            _entities["screenCam"],
            _collisionTypes);
    _entities["ground"] = factories::CreateGround(
            *_systems,
            _entities["screenCam"],
            _collisionTypes);

    _systems->GetCamera()[_entities["screenCam"]]->
        SetFollow(_systems->GetPhysics()[_entities["player"]]);
}

void GameScreen::Update(float delta)
{
    _systems->GetManager().Update(delta, UpdateStep::Update);
    _systems->GetManager().Update(delta, UpdateStep::Input);
}

void GameScreen::Draw(float delta)
{
    _manager.Window.clear(sf::Color::Blue);
    _systems->GetManager().Update(delta, UpdateStep::Draw);
}

