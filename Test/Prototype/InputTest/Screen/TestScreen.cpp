#include <SFML/Window.hpp>

#include "TestScreen.hpp"

#include <Ancona/Engine/EntityFramework/SystemManager.hpp>
#include <Ancona/Engine/Core/Systems/PositionSystem.hpp>
#include <Ancona/Engine/Core/Systems/InputControlSystem.hpp>
#include <Ancona/Game/InputDevices/PlayerKeyboard.hpp>
#include <Ancona/Game/Systems/PlayerInputComponent.hpp>
#include <Ancona/Engine/Core/Systems/SpriteSystem.hpp>

using namespace ild;

TestScreen::TestScreen(ScreenManager & manager)
    : AbstractScreen(manager)
{
    _systemManager = new SystemManager();
    _positionSystem = new PositionSystem(*_systemManager);
    _inputSystem = new InputControlSystem(*_systemManager); 
    _spriteSystem = new SpriteSystem(
            _manager.Window, *_systemManager, *_positionSystem);

    _player = _systemManager->CreateEntity();

    _positionSystem->CreateComponent(_player);
    PlayerKeyboard * keyboard = new PlayerKeyboard();
    PositionComponent * position = _positionSystem->at(_player);

    PlayerInputComponent * component = 
        new PlayerInputComponent(
                _player,
                *position,
                *keyboard);
    _inputSystem->AddComponent(_player, component);
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
