#include <Ancona/Core2D/Systems/Drawable/AnimatedDrawable.hpp>
#include <Ancona/Core2D/Systems/Physics/BasePhysicsSystem.hpp>
#include <Ancona/Util2D/VectorMath.hpp>

REGISTER_POLYMORPHIC_SERIALIZER(ild::AnimatedDrawable)

using namespace ild;

AnimatedDrawable::AnimatedDrawable(
        const int priority,
        const std::string & key,
        float duration,
        int priorityOffset,
        sf::Vector2f positionOffset) :
    Drawable(
            priority,
            key,
            priorityOffset,
            positionOffset),
    _duration(duration)
{
}

void AnimatedDrawable::OnDraw(sf::RenderWindow &window, sf::Transform drawableTransform, float delta)
{
    _frames[_curFrame]->Draw(window, drawableTransform, delta);
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
    for (auto & drawable : _frames)
    {
        drawable->FetchDependencies(entity);
    }
}

void AnimatedDrawable::Serialize(Archive &archive) {
    Drawable::Serialize(archive);
    archive(_duration, "duration");
    archive(_frames, "frames");
}

Drawable * AnimatedDrawable::FindDrawable(const std::string & key)
{
    Drawable * toReturn = Drawable::FindDrawable(key);
    if (toReturn == nullptr)
    {
        for (auto &drawable : _frames)
        {
            toReturn = drawable->FindDrawable(key);
            if (toReturn != nullptr)
            {
                break;
            }
        }
    }
    return toReturn;
}

void AnimatedDrawable::AddFrame(Drawable * frame)
{
    _frames.push_back(std::unique_ptr<Drawable>(frame));
}

void AnimatedDrawable::RemoveFrame(const std::string & key)
{
    _frames.erase(alg::remove_if(_frames, [key](const std::unique_ptr<Drawable> & drawable) {
        return key == drawable->key();
    }));
}

/* getters and setters */
sf::Vector2f AnimatedDrawable::size()
{
    return VectorMath::ComponentMultiplication(_frames[_curFrame]->size(), _scale);
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

