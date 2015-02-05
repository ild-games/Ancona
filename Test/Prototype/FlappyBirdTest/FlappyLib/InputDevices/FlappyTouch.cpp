#include "FlappyTouch.hpp"

#include <Ancona/Engine/InputDevices/Keyboard.hpp>
#include "../Systems/FlappyInputComponent.hpp"

using namespace ild;


FlappyTouch::FlappyTouch(
        ScreenManager & screenManager,
        MachineState initialState) : 
    FlappyInputHandler(screenManager, initialState)
{
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
        _screenManager.Replace(
                new FlappyScreen(
                    _screenManager, 
                    new FlappyTouch(_screenManager, FlappyStates::InAir),
                    false));
    }
}

void FlappyTouch::GameIntroInput(MachineState & curState)
{
    if(_gameSystems->GetPosition()[_player]->Position.y > 230)
    {
        _component->Jump();
    }
    if(sf::Touch::isDown(0))
    {
        _component->Jump();
        _gameSystems->GetPipeSpawner()[_pipeSpawner]->SetStopSpawning(false);
        _gameSystems->GetFadeDrawable().CreateComponent(
                _getReady,
                *_gameSystems->GetDrawable()[_getReady],
                false);
                
        ChangeState(FlappyStates::InAir);
    }
}
