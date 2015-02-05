#include <Ancona/Engine/Core/Systems/Drawable/AnimatedDrawable.hpp>

using namespace ild;

AnimatedDrawable::AnimatedDrawable(
        const PositionComponent & positionComponent, 
        const std::string textureKey,
        const RenderPriorityEnum priority,
        sf::Vector2f frameDimensions,
        int numFrames,
        int speed,
        float xGap,
        float yGap,
        int priorityOffset,
        sf::Vector2f positionOffset) :
    _frameDimensions(frameDimensions),
    _numFrames(numFrames),
    SPEED_CAP(numFrames),
    _speed(speed),
    _xGap(xGap),
    _yGap(yGap),
    SpriteDrawable(
            positionComponent,
            textureKey,
            priority,
            priorityOffset,
            positionOffset)
{
    _sprite->setTextureRect(
            sf::IntRect(
                _xGap, 
                _yGap, 
                _frameDimensions.x, 
                _frameDimensions.y));
    _sprite->setOrigin(
            _frameDimensions.x / 2,
            _frameDimensions.y / 2);
}

void AnimatedDrawable::Draw(sf::RenderWindow & window)
{
    _speed--;
    if(_speed == 0) 
    {
        _speed = SPEED_CAP;
        AdvanceFrame();
    }
    SpriteDrawable::Draw(window);
}

void AnimatedDrawable::AdvanceFrame()
{
    _curFrame++;
    if(_curFrame == _numFrames)
    {
        _curFrame = 0;
    }
    _sprite->setTextureRect(
            sf::IntRect(
                (_curFrame * _frameDimensions.x) + (_curFrame * _xGap), 
                0,
                _frameDimensions.x, 
                _frameDimensions.y));
}
