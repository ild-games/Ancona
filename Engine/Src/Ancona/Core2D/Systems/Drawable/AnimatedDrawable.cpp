#include <Ancona/Core2D/Systems/Drawable/AnimatedDrawable.hpp>
#include <Ancona/Core2D/Systems/Physics/BasePhysicsSystem.hpp>

REGISTER_POLYMORPHIC_SERIALIZER(ild::AnimatedDrawable)

using namespace ild;

AnimatedDrawable::AnimatedDrawable(
        BasePhysicsSystem * physicsSystem,
        const int priority,
        float duration,
        int priorityOffset,
        sf::Vector2f positionOffset) :
    Drawable(
            physicsSystem,
            priority,
            priorityOffset,
            positionOffset)
{
}

void AnimatedDrawable::Draw(sf::RenderWindow & window, sf::Transform transform, float delta)
{
    auto pos = _physicsComponent->GetInfo().position();
    sf::Vector2f position = sf::Vector2f(
            pos.x + _positionOffset.x,
            pos.y + _positionOffset.y);
    _frames[_curFrame]->position(position);
    _frames[_curFrame]->Draw(window, transform.combine(_transform), delta);

    Tick(delta);
}


void AnimatedDrawable::Tick(float delta)
{
    _timeUntilChange -= delta;
    if(_timeUntilChange <= 0)
    {
        _timeUntilChange += _duration;
        AdvanceFrame();
    }
}

void AnimatedDrawable::AdvanceFrame()
{
    _curFrame++;
    if(_curFrame == _frames.size())
    {
        _curFrame = 0;
    }
}

void AnimatedDrawable::FetchDependencies(const Entity &entity) {
    Drawable::FetchDependencies(entity);
    _timeUntilChange = _duration;
    _curFrame = 0;
    for(auto & frame : _frames)
    {
        frame->SetupSprite();
    }
}

void AnimatedDrawable::Serialize(Archive &archive) {
    Drawable::Serialize(archive);
    archive(_duration, "duration");
    archive(_frames, "frames");
}

/* getters and setters */
sf::Vector2u AnimatedDrawable::size()
{
    return _frames[_curFrame]->size();
}

int AnimatedDrawable::alpha()
{
    return _frames[_curFrame]->alpha();
}

void AnimatedDrawable::alpha(int newAlpha)
{
    for(auto & frame : _frames)
    {
        frame->alpha(newAlpha);
    }
}

