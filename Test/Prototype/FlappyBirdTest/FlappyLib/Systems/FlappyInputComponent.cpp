#include "FlappyInputComponent.hpp"
#include <SFML/System.hpp>

using namespace ild;

FlappyInputComponent::FlappyInputComponent(
        Entity & flapper,
        PositionComponent & positionComponent,
        FlappyRotateComponent & rotateComponent,
        FlappyTouch & inputHandler)
    : InputControlComponent(inputHandler),
      _positionComponent(positionComponent),
      _rotateComponent(rotateComponent)
{
    inputHandler.RegisterInputComponent(this);
}

FlappyInputComponent::FlappyInputComponent(
        Entity & flapper,
        PositionComponent & positionComponent,
        FlappyRotateComponent & rotateComponent,
        FlappyKeyboard & inputHandler)
    : InputControlComponent(inputHandler),
      _positionComponent(positionComponent),
      _rotateComponent(rotateComponent)
{
    inputHandler.RegisterInputComponent(this);
}

void FlappyInputComponent::Jump() 
{
    if(_positionComponent.Position.y > 30)
    {
        _rotateComponent.SetRotateDir(-1);
        _positionComponent.Velocity.y = -130;
    }
}
