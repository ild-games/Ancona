#include <iostream>
#include <Ancona/Engine/InputDevices/Keyboard.hpp>
#include "JumpyKeyboard.hpp"

using namespace ild;

enum direction {
    UP, RIGHT, DOWN, LEFT, NO_DIR
};
static Point directions []= {Point(0,-1),Point(1,0),Point(0,1),Point(-1,0)};

void JumpyKeyboard::RegisterInputComponent(JumpyInputComponent * component)
{
    _playerComponent = component;
}

void JumpyKeyboard::HandleInput()
{
    if(Keyboard::IsKeyDown(sf::Keyboard::Key::W))
    {
        _playerComponent->GoDirection(UP);
    }
    else if(Keyboard::IsKeyDown(sf::Keyboard::Key::A))
    {
        _playerComponent->GoDirection(LEFT);
    }
    else if(Keyboard::IsKeyDown(sf::Keyboard::Key::D))
    {
        _playerComponent->GoDirection(RIGHT);
    }
    else if(Keyboard::IsKeyDown(sf::Keyboard::Key::S))
    {
        _playerComponent->GoDirection(DOWN);
    } 
    else
    {
        _playerComponent->GoDirection(NO_DIR);
    }
}

JumpyInputComponent::JumpyInputComponent(const Entity & player, PlatformPhysicsComponent & physicsComponent, JumpyKeyboard & inputHandler)
    : InputControlComponent(inputHandler)
{
    inputHandler.RegisterInputComponent(this);
    action = physicsComponent.GetActions().CreateVelocityAction();
    action->Duration(ActionDuration::PERSISTENT)
          ->Tween(0.5);
}

void JumpyInputComponent::GoDirection(int direction)
{
    if(lastDir != direction)
    {
        lastDir = direction;
        action->ResetAge();
        action->Value(directions[direction] * 100.0f);
    }
}
