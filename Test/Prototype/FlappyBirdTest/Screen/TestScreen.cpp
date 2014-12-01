#include <SFML/Window.hpp>

#include "TestScreen.hpp"

#include <Ancona/Engine/EntityFramework/SystemManager.hpp>
#include <Ancona/Engine/Core/Systems/PositionSystem.hpp>
#include <Ancona/Engine/Core/Systems/InputControlSystem.hpp>
#include <Ancona/Game/InputDevices/PlayerKeyboard.hpp>
#include <Ancona/Game/Systems/PlayerInputComponent.hpp>
#include "../Systems/GravitySystem.hpp"
#include "../Systems/GravityComponent.hpp"
#include "../InputDevices/FlappyKeyboard.hpp"
#include "../Systems/FlappyInputComponent.hpp"
#include <Ancona/Engine/Core/Systems/SpriteSystem.hpp>

using namespace ild;

TestScreen::TestScreen(ScreenManager & manager)
    : AbstractScreen(manager)
{
    _systemManager = new SystemManager();
    _positionSystem = new PositionSystem(*_systemManager);
    _inputSystem = new InputControlSystem(*_systemManager); 
    _gravitySystem = new GravitySystem(*_systemManager);
    _spriteSystem = new SpriteSystem(
            _manager.Window, *_systemManager, *_positionSystem);

    _player = _systemManager->CreateEntity();

    // position component setup
    _positionSystem->CreateComponent(_player);
    PositionComponent * position = _positionSystem->at(_player);
    position->Position.x += 100;
    position->Position.y += 220;


    // input component setup
    FlappyKeyboard * keyboard = new FlappyKeyboard();
    FlappyInputComponent * component = 
        new FlappyInputComponent (
                _player,
                *position,
                *keyboard);
    _inputSystem->AddComponent(_player, component);

    // gravity component setup
    _gravitySystem->CreateComponent(_player, *position);
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

void TestScreen::Init()
{
    _spriteSystem->CreateComponent(_player,"player");
}
