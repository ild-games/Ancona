#include "FlappyRotateComponent.hpp"

using namespace ild;

FlappyRotateComponent::FlappyRotateComponent(
        SpriteComponent & spriteComponent, 
        PositionComponent & positionComponent)
    : _spriteComponent(spriteComponent), _positionComponent(positionComponent)
{
    _rotateDir = 1;
}

void FlappyRotateComponent::Update()
{
    if(_rotateDir == 1 && _positionComponent.Velocity.y > 0 && _spriteComponent.GetRotation() <= 90) 
    {
        _spriteComponent.SetRotation(_spriteComponent.GetRotation() + ROTATE_SPEED);
    } 
    else 
    {
        if(_rotateDir == -1 && _spriteComponent.GetRotation() >= -30.0f)
        {
            _spriteComponent.SetRotation(_spriteComponent.GetRotation() - (ROTATE_SPEED * 3));
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
