#include <SFML/Window.hpp>

#include "FlappyScreen.hpp"


#include <iostream>
#include <string>
#include <sstream>

#include "../EntityFactories/PlayerFactory.hpp"
#include "../EntityFactories/EnvironmentFactory.hpp"
#include "../InputDevices/FlappyInputHandler.hpp"
#include "../Systems/FlappyInputComponent.hpp"
#include "../Systems/FlappyRotateComponent.hpp"
#include "../Systems/PipeSpawnerComponent.hpp"
#include "../States/FlappyStates.hpp"

#include <Ancona/Engine/Core/Systems/InputControlSystem.hpp>
#include <Ancona/Game/Systems/PlayerInputComponent.hpp>
#include <Ancona/Game/InputDevices/PlayerKeyboard.hpp>
#include <Ancona/Game/Systems/PlayerInputComponent.hpp>

using namespace ild;

FlappyScreen::FlappyScreen(
        ScreenManager & manager, 
        FlappyInputHandler * inputHandler,
        bool showIntro) : 
    AbstractScreen(manager),
    _inputHandler(inputHandler),
    _showIntro(showIntro)
{
    _systems = new FlappyGameSystems(manager.Window);
    _collisionTypes["player"] = _systems->GetCollision().CreateType();
    _collisionTypes["ground"] = _systems->GetCollision().CreateType();
    _collisionTypes["groundWarp"] = _systems->GetCollision().CreateType();
    _collisionTypes["pipe"] = _systems->GetCollision().CreateType();
    _collisionTypes["point"] = _systems->GetCollision().CreateType();
}

void FlappyScreen::Init()
{
    // init ground
    _entities["ground"] = factories::CreateGround(
            _systems->GetManager(),
            _systems->GetPosition(),
            _systems->GetDrawable(),
            _systems->GetCollision(),
            _collisionTypes);

    // init pipe spawner
    _entities["pipeSpawner"] = factories::CreatePipeSpawner(
            _systems->GetManager(),
            _systems->GetPipeSpawner(),
            _systems->GetPosition(),
            _systems->GetDrawable(),
            _systems->GetCollision(),
            _collisionTypes);
    if(!_showIntro)
    {
        _systems->GetPipeSpawner()[_entities["pipeSpawner"]]->SetStopSpawning(false);
    }

    // init background
    _entities["bg"] = factories::CreateBackground(
            _systems->GetManager(),
            _systems->GetPosition(),
            _systems->GetDrawable());

    // init point counter
    _entities["pointCounter"] = factories::CreatePointCounter(
            _systems->GetManager(),
            _systems->GetPosition(),
            _systems->GetDrawable());

    // get ready 
    _entities["get-ready"] = factories::CreateGetReady(
            _systems->GetManager(),
            _systems->GetPosition(),
            _systems->GetDrawable());

    // init player
    _entities["player"] = factories::CreatePlayer(
            _systems,
            _collisionTypes,
            _entities,
            *_inputHandler);

    _inputHandler->SetPosition(_systems->GetPosition().at(_entities["player"]));
    _inputHandler->SetPipeSpawner(_systems->GetPipeSpawner().at(_entities["pipeSpawner"]));
}

void FlappyScreen::Update(float delta)
{
    _systems->GetManager().Update(delta,UpdateStep::Update);
    _systems->GetManager().Update(delta,UpdateStep::Input);
}

void FlappyScreen::Draw()
{
    _manager.Window.clear(sf::Color::Blue);
    _systems->GetManager().Update(0,UpdateStep::Draw);
}
