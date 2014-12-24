#include "FlappyKeyboard.hpp"
#include <Ancona/Engine/InputDevices/Keyboard.hpp>
#include "../Systems/FlappyInputComponent.hpp"

#include <SFML/Window.hpp>
#include <iostream>

using namespace ild;

FlappyKeyboard::FlappyKeyboard(ScreenManager & screenManager)
    : _machine(FlappyStates::Count), 
      _curState(FlappyStates::InAir), 
      _screenManager(screenManager)
{
    _machine.SetAction(FlappyStates::InAir, &FlappyKeyboard::InAirInput);
    _machine.SetAction(FlappyStates::OnGround, &FlappyKeyboard::OnGroundInput);
}

void FlappyKeyboard::HandleInput()
{
    _machine.Update(*this, _curState); 
}

void FlappyKeyboard::InAirInput(MachineState & curState)
{
    if(Keyboard::IsKeyPressed(sf::Keyboard::Key::Space))
    {
        _component->Jump();
    }
}

void FlappyKeyboard::OnGroundInput(MachineState & curState)
{
    if(Keyboard::IsKeyPressed(sf::Keyboard::Key::Space))
    {
        _screenManager.Replace(new TestScreen(_screenManager));
    }
}

void FlappyKeyboard::RegisterInputComponent(
        FlappyInputComponent * component)
{
    _component = component;
}

void FlappyKeyboard::ChangeState(const MachineState & newState)
{
    _curState = newState;
}
