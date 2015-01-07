#include "FlappyTouch.hpp"
#include "../Systems/FlappyInputComponent.hpp"

#include <SFML/Window.hpp>

using namespace ild;


FlappyTouch::FlappyTouch(ScreenManager & screenManager)
    : _machine(FlappyStates::Count), 
      _curState(FlappyStates::InAir), 
      _screenManager(screenManager)
{
    _machine.SetAction(FlappyStates::InAir, &FlappyTouch::InAirInput);
    _machine.SetAction(FlappyStates::OnGround, &FlappyTouch::OnGroundInput);
}


void FlappyTouch::HandleInput()
{
    _machine.Update(*this, _curState);
}

void FlappyTouch::InAirInput(MachineState & curState)
{
    if(sf::Touch::isDown(0))
    {
        _component->Jump();
    }
}

void FlappyTouch::OnGroundInput(MachineState & curState)
{
    if(sf::Touch::isDown(0))
    {
        _screenManager.Replace(new TestScreen(_screenManager));
    }
}

void FlappyTouch::RegisterInputComponent(FlappyInputComponent * component)
{
    _component = component;
}

void FlappyTouch::ChangeState(const MachineState & newState)
{
    if(AllowedTransition(newState)) 
    {
        _curState = newState;
    }
}

bool FlappyTouch::AllowedTransition(const MachineState & newState)
{
    switch(_curState)
    {
        case FlappyStates::InAir:
            return InAirTransitionCheck(newState);
            break;
    }
    return false;
}

bool FlappyTouch::InAirTransitionCheck(const MachineState & newState)
{
    return newState == FlappyStates::OnGround;
}
