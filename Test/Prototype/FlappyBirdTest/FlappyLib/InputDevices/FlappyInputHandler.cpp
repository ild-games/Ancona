#include "FlappyInputHandler.hpp"
#include "../Systems/FlappyInputComponent.hpp"

using namespace ild;

FlappyInputHandler::FlappyInputHandler(ScreenManager & screenManager) : 
    _machine(FlappyStates::Count),
    _curState(FlappyStates::InAir),
    _screenManager(screenManager)
{
    _machine.SetAction(FlappyStates::InAir, &FlappyInputHandler::InAirInput);
    _machine.SetAction(FlappyStates::OnGround, &FlappyInputHandler::OnGroundInput);
}

void FlappyInputHandler::HandleInput()
{
    _machine.Update(*this, _curState); 
}

void FlappyInputHandler::RegisterInputComponent(
        FlappyInputComponent * component)
{
    _component = component;
}

void FlappyInputHandler::ChangeState(const MachineState & newState)
{
    if(AllowedTransition(newState)) 
    {
        _curState = newState;
    }
}

bool FlappyInputHandler::AllowedTransition(const MachineState & newState)
{
    switch(_curState)
    {
        case FlappyStates::InAir:
            return InAirTransitionCheck(newState);
            break;
    }
    return false;
}

bool FlappyInputHandler::InAirTransitionCheck(const MachineState & newState)
{
    return newState == FlappyStates::OnGround;
}

void FlappyInputHandler::SetPosition(PositionComponent * position)
{
    _position = position;
}
