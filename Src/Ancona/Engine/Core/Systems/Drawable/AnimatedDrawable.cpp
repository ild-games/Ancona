#include <Ancona/Engine/Core/Systems/Drawable/AnimatedDrawable.hpp>
#include <Ancona/Engine/Core/Systems/Physics/PlatformPhysicsSystem.hpp>

using namespace ild;

AnimatedDrawable::AnimatedDrawable(
        const BasePhysicsComponent & physicsComponent, 
        const std::string textureKey,
        const int priority,
        sf::Vector2f frameDimensions,
        int numFrames,
        float duration,
        int priorityOffset,
        sf::Vector2f positionOffset) :
    SpriteDrawable(
            physicsComponent,
            textureKey,
            priority,
            priorityOffset,
            positionOffset),
    _frameDimensions(frameDimensions),
    DURATION(duration),
    _timeUntilChange(duration),
    _numFrames(numFrames)
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

void * AnimatedDrawable::Inflate(
        const Json::Value & object,
        const Entity entity,
        LoadingContext * loadingContext)
{
    AnimatedDrawable * animation = new AnimatedDrawable(
            *loadingContext->GetSystems().GetSystem<PlatformPhysicsSystem>("physics")->at(entity),
            object["texture-key"].asString(),
            object["render-priority"].asInt(),
            sf::Vector2f(object["frame-dim"]["width"].asFloat(), object["frame-dim"]["height"].asFloat()),
            object["num-frames"].asInt(),
            object["duration"].asFloat(),
            object["priority-offset"].asInt(),
            sf::Vector2f(object["position-offset"]["x"].asFloat(), object["position-offset"]["y"].asFloat()));
    return animation;
}
