#include "FlappyKeyboard.hpp"
#include <Ancona/Engine/InputDevices/Keyboard.hpp>
#include "../Systems/FlappyInputComponent.hpp"

#include <SFML/Window.hpp>

using namespace ild;

void FlappyKeyboard::HandleInput()
{
    if(Keyboard::IsKeyPressed(sf::Keyboard::Key::Space))
    {
        _component->Jump();
    }
}

void FlappyKeyboard::RegisterInputComponent(
        FlappyInputComponent * component)
{
    _component = component;
}
