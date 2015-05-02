#include <Mallard/GameLib/InputDevices/PlayerKeyboard.hpp>
#include <Ancona/Core2D/InputDevices/Keyboard.hpp>
#include <Mallard/GameLib/Systems/PlayerInputComponent.hpp>

#include <SFML/Window.hpp>
#include <iostream>
#include <Mallard/GameLib/Screens/GameScreen.hpp>

using namespace ild;

PlayerKeyboard::PlayerKeyboard(
        ScreenManager & screenManager) :
    _screenManager(screenManager)
{
}

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
    if(Keyboard::IsKeyPressed(sf::Keyboard::Key::R))
    {
        _screenManager.Replace(new GameScreen(_screenManager, 0));
    }

    _component->Move(direction);
}

void PlayerKeyboard::RegisterInputComponent(
        PlayerInputComponent * component)
{
    _component = component;
}
