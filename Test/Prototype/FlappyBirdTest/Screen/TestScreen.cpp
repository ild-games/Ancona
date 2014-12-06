#include <SFML/Window.hpp>

#include "TestScreen.hpp"

#include <iostream>

#include <Ancona/Engine/EntityFramework/SystemManager.hpp>
#include <Ancona/Engine/Core/Systems/PositionSystem.hpp>
#include <Ancona/Engine/Core/Systems/InputControlSystem.hpp>
#include <Ancona/Game/InputDevices/PlayerKeyboard.hpp>
#include <Ancona/Game/Systems/PlayerInputComponent.hpp>
#include "../Systems/GravitySystem.hpp"
#include "../Systems/GravityComponent.hpp"
#include "../InputDevices/FlappyKeyboard.hpp"
#include "../Systems/FlappyInputComponent.hpp"
#include "../Systems/FlappyRotateSystem.hpp"
#include "../Systems/FlappyRotateComponent.hpp"
#include "../Systems/PipeSpawnerSystem.hpp"
#include "../Systems/PipeSpawnerComponent.hpp"
#include <Ancona/Engine/Core/Systems/SpriteSystem.hpp>

using namespace ild;

TestScreen::TestScreen(ScreenManager & manager)
    : AbstractScreen(manager)
{
    _systemManager = new SystemManager();
    _positionSystem = new PositionSystem(*_systemManager);
    _inputSystem = new InputControlSystem(*_systemManager); 
    _gravitySystem = new GravitySystem(*_systemManager);
    _rotateSystem = new FlappyRotateSystem(*_systemManager);
    _pipeSpawnerSystem = new PipeSpawnerSystem(*_systemManager);
    _spriteSystem = new SpriteSystem(
            _manager.Window, *_systemManager, *_positionSystem);
}

void TestScreen::Update(float delta)
{
    _systemManager->Update(delta,UpdateStep::Update);
    _systemManager->Update(delta,UpdateStep::Input);

    //DEBUG
    if(_positionSystem->at(_ground)->Position.x < -240)
    {
        _positionSystem->at(_ground)->Position.x = 0;
    }
    //ENDDEBUG
}

void TestScreen::Draw()
{
    _manager.Window.clear(sf::Color::Green);
    _systemManager->Update(0,UpdateStep::Draw);
}

void TestScreen::Init()
{
    // player entity setup
    _player = _systemManager->CreateEntity();

    // position component setup
    _positionSystem->CreateComponent(_player);
    PositionComponent * position = _positionSystem->at(_player);
    position->Position.x += 100;
    position->Position.y += 220;

    // sprite system setup
    _spriteSystem->CreateComponent(_player,"flappy",RenderPriority::Player);
    SpriteComponent * sprite = _spriteSystem->at(_player);
    sprite->SetRotation(-30.0f);
    sprite->GetSprite()->setOrigin(8.0f, 8.0f);
    
    // rotate component setup
    _rotateSystem->CreateComponent(_player, *sprite, *position);
    FlappyRotateComponent * rotate = _rotateSystem->at(_player);

    // input component setup
    FlappyKeyboard * keyboard = new FlappyKeyboard();
    FlappyInputComponent * inputComponent = 
        new FlappyInputComponent (
                _player,
                *position,
                *rotate,
                *keyboard);
    _inputSystem->AddComponent(_player, inputComponent);

    // gravity component setup
    _gravitySystem->CreateComponent(_player, *position);

    // pipe spawner setup
    _pipeSpawner = _systemManager->CreateEntity();
    _pipeSpawnerSystem->CreateComponent(
            _pipeSpawner, 
            *_spriteSystem, 
            *_positionSystem,
            *_systemManager);

    // bg and fg setup
    _fg = _systemManager->CreateEntity();
    _positionSystem->CreateComponent(_fg);
    _spriteSystem->CreateComponent(_fg, "flappy-fg", RenderPriority::Background, 1);
    _bg = _systemManager->CreateEntity();
    _positionSystem->CreateComponent(_bg);
    if(rand() % 2 == 1)
    {
        _spriteSystem->CreateComponent(_bg, "flappy-bg1", RenderPriority::Background);
    }
    else 
    {
        _spriteSystem->CreateComponent(_bg, "flappy-bg2", RenderPriority::Background);
    }

    // ground setup
    _ground = _systemManager->CreateEntity();
    PositionComponent * groundPosition = _positionSystem->CreateComponent(_ground);
    groundPosition->Position.y += 300;
    groundPosition->Velocity.x = -65.0f;
    _spriteSystem->CreateComponent(_ground, "flappy-ground", RenderPriority::Foreground);
}
