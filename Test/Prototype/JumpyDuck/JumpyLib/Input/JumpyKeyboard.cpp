#include <iostream>
#include <Ancona/Engine/InputDevices/Keyboard.hpp>
#include "JumpyKeyboard.hpp"

using namespace ild;

void JumpyKeyboard::RegisterInputComponent(JumpyInputComponent * component)
{
    _playerComponent = component;
}

void JumpyKeyboard::HandleInput()
{
    if(Keyboard::IsKeyPressed(sf::Keyboard::Key::W))
    {
        _playerComponent->GoUp();
    }
    if(Keyboard::IsKeyPressed(sf::Keyboard::Key::A))
    {
        _playerComponent->GoLeft();
    }
    if(Keyboard::IsKeyPressed(sf::Keyboard::Key::D))
    {
        _playerComponent->GoRight();
    }
    if(Keyboard::IsKeyPressed(sf::Keyboard::Key::S))
    {
        _playerComponent->GoDown();
    }
}

JumpyInputComponent::JumpyInputComponent(const Entity & player, PlatformPhysicsComponent & physicsComponent, JumpyKeyboard & inputHandler)
    : InputControlComponent(inputHandler)
{
    inputHandler.RegisterInputComponent(this);
}

void JumpyInputComponent::GoLeft()
{
    std::cout << "Go left" << std::endl;
}

void JumpyInputComponent::GoRight()
{
    std::cout << "Go right" << std::endl;
}

void JumpyInputComponent::GoUp()
{
    std::cout << "Go up" << std::endl;
}

void JumpyInputComponent::GoDown()
{
    std::cout << "Go down" << std::endl;
}
