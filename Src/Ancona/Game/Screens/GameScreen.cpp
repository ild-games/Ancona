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
    _entities["player"] = factories::CreatePlayer(
            _systems,
            _collisionTypes);

    _entities["ground"] = factories::CreateGround(
            _systems,
            _collisionTypes);
}

void GameScreen::Update(float delta)
{
    _systems->GetManager().Update(delta, UpdateStep::Update);
    _systems->GetManager().Update(delta, UpdateStep::Input);
}

void GameScreen::Draw()
{
    _manager.Window.clear(sf::Color::Blue);
    _systems->GetManager().Update(0, UpdateStep::Draw);
}

