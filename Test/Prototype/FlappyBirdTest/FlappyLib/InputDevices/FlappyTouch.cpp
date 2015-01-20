#include "FlappyTouch.hpp"

#include <Ancona/Engine/InputDevices/Keyboard.hpp>
#include "../Systems/FlappyInputComponent.hpp"

using namespace ild;


FlappyTouch::FlappyTouch(ScreenManager & screenManager) : 
    FlappyInputHandler(screenManager)
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
                new FlappyScreen(_screenManager, new FlappyTouch(_screenManager)));
    }
}
