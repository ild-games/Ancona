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
#include <Ancona/Engine/Core/Systems/Collision/CollisionSystem.hpp>

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
    _collisionSystem = new CollisionSystem(*_systemManager, *_positionSystem);
    _spriteSystem = new SpriteSystem(
            _manager.Window, *_systemManager, *_positionSystem);
}

void TestScreen::Init()
{
    InitializeEntities();
}

void TestScreen::Update(float delta)
{
    _systemManager->Update(delta,UpdateStep::Update);
    _systemManager->Update(delta,UpdateStep::Input);
}

void TestScreen::Draw()
{
    _manager.Window.clear(sf::Color::Green);
    _systemManager->Update(0,UpdateStep::Draw);
}

void TestScreen::InitializeEntities()
{
    CreateGround();
    CreatePipeSpawner();
    CreateFgBg();
    CreatePlayer();
}

void TestScreen::CreateGround()
{
    // ground setup
    _ground = _systemManager->CreateEntity();
    PositionComponent * groundPosition = _positionSystem->CreateComponent(_ground);
    groundPosition->Position.y = 340;
    groundPosition->Velocity.x = -65.0f;
    _spriteSystem->CreateComponent(_ground, "flappy-ground", RenderPriority::Player, -1);
    _groundCollisionType = _collisionSystem->CreateType();
    CollisionComponent * groundColComponent = _collisionSystem->CreateComponent(
            _ground,
            sf::Vector3f(540, 80, 0),
            _groundCollisionType);

    // ground warp setup
    _groundWarp = _systemManager->CreateEntity();
    PositionComponent * groundWarpPosition = _positionSystem->CreateComponent(_groundWarp);
    groundWarpPosition->Position.x = -210;
    groundWarpPosition->Position.y = 340;
    CollisionType groundWarpCollisionType = _collisionSystem->CreateType();
    CollisionComponent * groundWarpColComponent = _collisionSystem->CreateComponent(
            _groundWarp,
            sf::Vector3f(5, 5, 0),
            groundWarpCollisionType);

    // setup ground warp/ground collision response
    _collisionSystem->SetHandler(
            _groundCollisionType, 
            groundWarpCollisionType,
            [=](Entity ground, Entity groundWarp)
            {
                _positionSystem->at(_ground)->Position.x = 270;
            });
}

void TestScreen::CreatePipeSpawner() 
{
    // pipe spawner setup
    _pipeSpawner = _systemManager->CreateEntity();
    _pipeCollisionType = _collisionSystem->CreateType();
    _pipeSpawnerComp = _pipeSpawnerSystem->CreateComponent(
            _pipeSpawner, 
            *_spriteSystem, 
            *_positionSystem,
            *_collisionSystem,
            *_systemManager,
            _pipeCollisionType);
}

void TestScreen::CreateFgBg() 
{
    // bg and fg setup
    _fg = _systemManager->CreateEntity();
    PositionComponent * fgPos = _positionSystem->CreateComponent(_fg);
    fgPos->Position.x = 136; 
    fgPos->Position.y = 200; 
    _spriteSystem->CreateComponent(_fg, "flappy-fg", RenderPriority::Background, 1);
    _bg = _systemManager->CreateEntity();
    PositionComponent * bgPos = _positionSystem->CreateComponent(_bg);
    bgPos->Position.x = 320;
    bgPos->Position.y = 240;
    if(rand() % 2 == 1)
    {
        _spriteSystem->CreateComponent(_bg, "flappy-bg1", RenderPriority::Background);
    }
    else 
    {
        _spriteSystem->CreateComponent(_bg, "flappy-bg2", RenderPriority::Background);
    }
}

void TestScreen::CreatePlayer() 
{
    // player entity setup
    _player = _systemManager->CreateEntity();

    // collision type setup
    CollisionType playerCollisionType = _collisionSystem->CreateType();

    // position component setup
    _positionSystem->CreateComponent(_player);
    PositionComponent * position = _positionSystem->at(_player);
    position->Position.x += 100;
    position->Position.y += 220;

    // sprite system setup
    _spriteSystem->CreateComponent(_player,"flappy",RenderPriority::Player);
    SpriteComponent * sprite = _spriteSystem->at(_player);
    sprite->SetRotation(-30.0f);
    
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

    // collision component setup for player
    CollisionComponent * playerColComponent = _collisionSystem->CreateComponent(
            _player,
            sf::Vector3f(14.0f, 14.0f, 0),
            playerCollisionType);
    _collisionSystem->SetHandler(
            playerCollisionType, 
            _pipeCollisionType,
            [=](Entity player, Entity pipe)
            {
                StopAllMovement();
            });
    _collisionSystem->SetHandler(
            playerCollisionType,
            _groundCollisionType,
            [=](Entity player, Entity ground)
            {
                StopAllMovement();
                _positionSystem->at(player)->Velocity.y = 0;
            });
}


void TestScreen::StopAllMovement()
{
    _pipeSpawnerComp->StopMovingPipes();
    _positionSystem->at(_ground)->Velocity.x = 0;
    if(_positionSystem->at(_player)->Velocity.y < 0)
    {
        _positionSystem->at(_player)->Velocity.y = 0;
    }
    if(_inputSystem->at(_player) != NULL)
    {
        _inputSystem->RemoveComponent(_player);
    }
}
