#include <iostream>

#include <Ancona/Game/Systems/PlayerInputComponent.hpp>
#include <SFML/System.hpp>

using namespace ild;

const float VELOCITY = 0.01;

const int PlayerDirection::Up = 1 << 0;
const int PlayerDirection::Down = 1 << 1;
const int PlayerDirection::Left = 1 << 2;
const int PlayerDirection::Right = 1 << 3;
const int PlayerDirection::None = 0;

PlayerInputComponent::PlayerInputComponent(
        Entity & player,
        PositionComponent & positionComponent,
        PlayerKeyboard & inputHandler)
    : InputControlComponent(inputHandler), 
      _positionComponent(positionComponent)
{
    inputHandler.RegisterInputComponent(this);
}

void PlayerInputComponent::Move(PlayerDirectionEnum direction)
{
    sf::Vector3f directionVector;
    if(direction & PlayerDirection::Up)
    {
        directionVector.y -= VELOCITY;
    }
    if(direction & PlayerDirection::Down)
    {
        directionVector.y += VELOCITY;
    }
    if(direction & PlayerDirection::Left)
    {
        directionVector.x -= VELOCITY;
    }
    if(direction & PlayerDirection::Right)
    {
        directionVector.x += VELOCITY;
    }

    _positionComponent.Velocity = directionVector;
}
