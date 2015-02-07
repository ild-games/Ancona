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
    float rotation = _drawableComponent.GetDrawable("player-sprite")->GetRotation();
    if(_rotateDir == 1 && _positionComponent.Velocity.y > 0 && rotation <= 90) 
    {
        float rotateAmount = ROTATE_SPEED * delta;
        _drawableComponent.GetDrawable("player-sprite")->SetRotation(rotation + rotateAmount);
    } 
    else 
    {
        if(_rotateDir == -1 && rotation >= -30.0f)
        {
            float rotateAmount = (ROTATE_SPEED * 3) * delta;
            _drawableComponent.GetDrawable("player-sprite")->SetRotation(rotation - rotateAmount);
        } 
        else 
        {
            _rotateDir = 1;
        }
    }
}
