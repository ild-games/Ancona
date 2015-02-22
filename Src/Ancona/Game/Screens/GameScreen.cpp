#include <Ancona/Game/EntityFactories/EnvironmentFactory.hpp>
#include <Ancona/Game/EntityFactories/PlayerFactory.hpp>
#include <Ancona/Game/Screens/GameScreen.hpp>

using namespace ild;

GameScreen::GameScreen(ScreenManager & manager) :
        AbstractScreen(manager, "game")
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
    _systems->GetDrawable().SetDefaultCamera(_systems->GetCamera()[_entities["screenCam"]]);
    _entities["player"] = factories::CreatePlayer(
            _systems,
            _collisionTypes);
    _entities["ground"] = factories::CreateGround(
            *_systems,
            _collisionTypes);

    _systems->GetCamera()[_entities["screenCam"]]->
        SetFollow(_systems->GetPhysics()[_entities["player"]]);
}

void GameScreen::Update(float delta)
{
    _systems->GetManager().Update(delta, UpdateStep::Update);
    _systems->GetManager().Update(delta, UpdateStep::Input);
    float newScale = _systems->GetCamera()[_entities["screenCam"]]->GetScale() - (0.1f * delta);
    _systems->GetCamera()[_entities["screenCam"]]->SetScale(newScale);
}

void GameScreen::Draw(float delta)
{
    _manager.Window.clear(sf::Color::Blue);
    _systems->GetManager().Update(delta, UpdateStep::Draw);
}

