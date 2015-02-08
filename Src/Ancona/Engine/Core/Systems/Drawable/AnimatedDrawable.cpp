#include <Ancona/Engine/Core/Systems/Drawable/AnimatedDrawable.hpp>

using namespace ild;

AnimatedDrawable::AnimatedDrawable(
        const PositionComponent & positionComponent, 
        const std::string textureKey,
        const int priority,
        sf::Vector2f frameDimensions,
        int numFrames,
        float duration,
        int priorityOffset,
        sf::Vector2f positionOffset) :
    _frameDimensions(frameDimensions),
    _numFrames(numFrames),
    DURATION(duration),
    _timeUntilChange(duration),
    SpriteDrawable(
            positionComponent,
            textureKey,
            priority,
            priorityOffset,
            positionOffset)
{
    _sprite->setTextureRect(
            sf::IntRect(
                0,
                0,
                _frameDimensions.x, 
                _frameDimensions.y));
    _sprite->setOrigin(
            _frameDimensions.x / 2,
            _frameDimensions.y / 2);
}

void AnimatedDrawable::Draw(sf::RenderWindow & window, float delta)
{
    _timeUntilChange -= delta;
    if(_timeUntilChange <= 0) 
    {
        _timeUntilChange += DURATION;
        AdvanceFrame();
    }
    SpriteDrawable::Draw(window, delta);
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
                _curFrame * _frameDimensions.x,
                0,
                _frameDimensions.x, 
                _frameDimensions.y));
}
