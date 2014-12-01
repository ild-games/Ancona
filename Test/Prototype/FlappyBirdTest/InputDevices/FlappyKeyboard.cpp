#include "FlappyKeyboard.hpp"
#include <Ancona/Engine/InputDevices/Keyboard.hpp>
#include "../Systems/FlappyInputComponent.hpp"

#include <SFML/Window.hpp>
#include <iostream>

using namespace ild;

void FlappyKeyboard::HandleInput()
{
    if(Keyboard::IsKeyPressed(sf::Keyboard::Key::Space))
    {
        std::cout << "Flappy Jump!" << std::endl;
        _component->Jump();
    }
}

void FlappyKeyboard::RegisterInputComponent(
        FlappyInputComponent * component)
{
    _component = component;
}
