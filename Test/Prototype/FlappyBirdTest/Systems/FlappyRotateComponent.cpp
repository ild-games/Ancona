#include "FlappyRotateComponent.hpp"

#include <iostream>

using namespace ild;

FlappyRotateComponent::FlappyRotateComponent(
        SpriteComponent & spriteComponent, 
        PositionComponent & positionComponent)
    : _spriteComponent(spriteComponent), _positionComponent(positionComponent)
{
    _rotateDir = 1;
}

void FlappyRotateComponent::Update(float delta)
{
    if(_rotateDir == 1 && _positionComponent.Velocity.y > 0 && _spriteComponent.GetRotation() <= 90) 
    {
        float rotateAmount = ROTATE_SPEED * delta;
        _spriteComponent.SetRotation(_spriteComponent.GetRotation() + rotateAmount);
    } 
    else 
    {
        if(_rotateDir == -1 && _spriteComponent.GetRotation() >= -30.0f)
        {
            float rotateAmount = (ROTATE_SPEED * 3) * delta;
            _spriteComponent.SetRotation(_spriteComponent.GetRotation() - rotateAmount);
        } 
        else 
        {
            _rotateDir = 1;
        }
    }
}

/* getters and setters */
int FlappyRotateComponent::GetRotateDir()
{
    return _rotateDir;
}
void FlappyRotateComponent::SetRotateDir(int rotateDir)
{
    _rotateDir = rotateDir;
}
