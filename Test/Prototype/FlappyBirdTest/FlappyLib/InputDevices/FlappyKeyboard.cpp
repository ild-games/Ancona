#include "FlappyKeyboard.hpp"

#include <Ancona/Engine/InputDevices/Keyboard.hpp>
#include "../Systems/FlappyInputComponent.hpp"

using namespace ild;

FlappyKeyboard::FlappyKeyboard(ScreenManager & screenManager) :
    FlappyInputHandler(screenManager)
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
                new FlappyScreen(_screenManager, new FlappyKeyboard(_screenManager)));
    }
}


