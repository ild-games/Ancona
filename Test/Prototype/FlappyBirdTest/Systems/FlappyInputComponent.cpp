#include "FlappyInputComponent.hpp"
#include <SFML/System.hpp>

using namespace ild;

FlappyInputComponent::FlappyInputComponent(
        Entity & flapper,
        PositionComponent & positionComponent,
        FlappyKeyboard & inputHandler)
    : InputControlComponent(inputHandler),
      _positionComponent(positionComponent)
{
    inputHandler.RegisterInputComponent(this);
}

void FlappyInputComponent::Jump() 
{
    _positionComponent.Velocity.y = -130;
}
