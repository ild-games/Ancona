#include "FlappyRotateComponent.hpp"

#include <iostream>

using namespace ild;

FlappyRotateComponent::FlappyRotateComponent(
        DrawableComponent & drawableComponent, 
        PositionComponent & positionComponent)
    : _drawableComponent(drawableComponent), _positionComponent(positionComponent)
{
    _rotateDir = 1;
}

void FlappyRotateComponent::Update(float delta)
{
    if(_rotateDir == 1 && _positionComponent.Velocity.y > 0 && _drawableComponent.GetRotation() <= 90) 
    {
        float rotateAmount = ROTATE_SPEED * delta;
        _drawableComponent.SetRotation(_drawableComponent.GetRotation() + rotateAmount);
    } 
    else 
    {
        if(_rotateDir == -1 && _drawableComponent.GetRotation() >= -30.0f)
        {
            float rotateAmount = (ROTATE_SPEED * 3) * delta;
            _drawableComponent.SetRotation(_drawableComponent.GetRotation() - rotateAmount);
        } 
        else 
        {
            _rotateDir = 1;
        }
    }
}
