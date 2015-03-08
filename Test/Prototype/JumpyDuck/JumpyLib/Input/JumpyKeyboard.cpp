#include <iostream>
#include <Ancona/Engine/InputDevices/Keyboard.hpp>
#include "JumpyKeyboard.hpp"

using namespace ild;

enum direction {
    UP, RIGHT, DOWN, LEFT, NO_DIR
};
static Point directions []= {Point(0,-1),Point(1,0),Point(0,1),Point(-1,0),Point(0,0)};

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

    if(Keyboard::IsKeyDown(sf::Keyboard::Space))
    {
        _playerComponent->Jump();
    }
}

JumpyInputComponent::JumpyInputComponent(const Entity & player, PlatformPhysicsComponent & physicsComponent, JumpyKeyboard & inputHandler)
    : InputControlComponent(inputHandler),_physics(physicsComponent)
{
    inputHandler.RegisterInputComponent(this);
    action = physicsComponent.GetActions().CreateVelocityAction();
    action->Duration(ActionDuration::PERSISTENT)
          ->Tween(0.5);

    jumpAction = physicsComponent.GetActions().CreateVelocityAction();
    jumpAction
        ->Duration(ActionDuration::PERSISTENT);
}

void JumpyInputComponent::Jump()
{
    if(_physics.GetInfo().IsOnGround())
    {
        jumpAction->Value(200.0f * directions[UP]);
    }
}

void JumpyInputComponent::GoDirection(int direction)
{
    if(_physics.GetInfo().IsOnGround() != _isOnGround)
    {
        _isOnGround = _physics.GetInfo().IsOnGround();

        if(_isOnGround)
        {
            jumpAction->Value(Point());
        }

        action->RelativeToGround(_isOnGround);
        lastDir = NO_DIR;
    } 

    Move(direction);
}

void JumpyInputComponent::Move(int direction)
{
    float speed = _isOnGround ? 100.0f : 50.0f;

    if(lastDir != direction)
    {
        if(direction == RIGHT || direction == LEFT)
        {

            action->ResetAge();
            action->Value(directions[direction] * speed);
        } 
        else
        {
            action->Value(Point());
        }
        lastDir = direction;
    } 
}
