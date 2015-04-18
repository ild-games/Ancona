#include <Ancona/Engine/Core/Systems/Drawable/AnimatedDrawable.hpp>
#include <Ancona/Engine/Core/Systems/Physics/BasePhysicsSystem.hpp>

REGISTER_POLYMORPHIC_SERIALIZER(ild::AnimatedDrawable)

using namespace ild;

AnimatedDrawable::AnimatedDrawable(
        BasePhysicsSystem * physicsSystem,
        const std::string textureKey,
        const int priority,
        sf::Vector2f frameDimensions,
        int numFrames,
        float duration,
        int priorityOffset,
        sf::Vector2f positionOffset) :
    SpriteDrawable(
            physicsSystem,
            textureKey,
            priority,
            priorityOffset,
            positionOffset),
    _frameDimensions(frameDimensions),
    _numFrames(numFrames)
{
}

void AnimatedDrawable::Draw(sf::RenderWindow & window, float delta)
{
    _timeUntilChange -= delta;
    if(_timeUntilChange <= 0) 
    {
        _timeUntilChange += _duration;
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
    float newX = _sprite->getTextureRect().left + _frameDimensions.x;
    float newY = _sprite->getTextureRect().top;
    if(newX >= _sprite->getTexture()->getSize().x)
    {
        newX = 0;
        newY += _frameDimensions.y;
        if(newY >= _sprite->getTexture()->getSize().y)
        {
            newY = 0;
        }
    }
    _sprite->setTextureRect(
            sf::IntRect(
                newX,
                newY,
                _frameDimensions.x, 
                _frameDimensions.y));
}

void AnimatedDrawable::FetchDependencies(const Entity &entity) {
    SpriteDrawable::FetchDependencies(entity);
    _timeUntilChange = _duration;
    _curFrame = 0;
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

void AnimatedDrawable::Serialize(Archive &archive) {
    SpriteDrawable::Serialize(archive);
    archive(_frameDimensions, "frame-dimensions");
    archive(_numFrames, "num-frames");
    archive(_duration, "duration");
}
