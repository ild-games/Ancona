#include <Ancona/Game/InputDevices/PlayerKeyboard.hpp>
#include <Ancona/Engine/InputDevices/Keyboard.hpp>
#include <Ancona/Game/Systems/PlayerInputComponent.hpp>

#include <SFML/Window.hpp>
#include <iostream>

using namespace ild;

void PlayerKeyboard::HandleInput()
{
    if(Keyboard::IsKeyPressed(sf::Keyboard::Key::Space))
    {
        std::cout << "Space Pressed" << std::endl;
    }

    PlayerDirectionEnum direction = PlayerDirection::None;

    if(Keyboard::IsKeyDown(sf::Keyboard::Key::W))
    {
        direction = direction | PlayerDirection::Up;
    }
            
    if(Keyboard::IsKeyDown(sf::Keyboard::Key::S))
    {
        direction = direction | PlayerDirection::Down;
    }

    if(Keyboard::IsKeyDown(sf::Keyboard::Key::A))
    {
        direction = direction | PlayerDirection::Left;
    }

    if(Keyboard::IsKeyDown(sf::Keyboard::Key::D))
    {
        direction = direction | PlayerDirection::Right;
    }

    _component->Move(direction);
}

void PlayerKeyboard::RegisterInputComponent(
        PlayerInputComponent * component)
{
    _component = component;
}
