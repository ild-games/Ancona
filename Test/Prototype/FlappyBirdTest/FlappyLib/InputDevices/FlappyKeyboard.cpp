#include "FlappyKeyboard.hpp"

#include <Ancona/Framework/InputDevices/Keyboard.hpp>
#include "../Systems/FlappyInputComponent.hpp"

using namespace ild;

FlappyKeyboard::FlappyKeyboard(
        ScreenManager & screenManager, 
        MachineState initialState) :
    FlappyInputHandler(screenManager, initialState)
{
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
        _screenManager.Replace(
                new FlappyScreen(
                    _screenManager, 
                    new FlappyKeyboard(_screenManager, FlappyStates::InAir),
                    false));
    }
}

void FlappyKeyboard::GameIntroInput(MachineState & curState)
{
    if(_gameSystems->GetPosition()[_player]->Position.y > 230)
    {
        _component->Jump();
    }
    if(Keyboard::IsKeyPressed(sf::Keyboard::Key::Space))
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
