#include <Ancona/Core2D/Systems/Drawable/AnimatedDrawable.hpp>
#include <Ancona/Core2D/Systems/Position/PositionSystem.hpp>
#include <Ancona/Util2D/VectorMath.hpp>

REGISTER_POLYMORPHIC_SERIALIZER(ild::AnimatedDrawable)

using namespace ild;

AnimatedDrawable::AnimatedDrawable(
        const int priority,
        const std::string & key,
        float duration,
        int priorityOffset,
        sf::Vector2f anchor) :
    Drawable(
            priority,
            key,
            priorityOffset,
            anchor),
    _duration(duration)
{
}

void AnimatedDrawable::OnDraw(sf::RenderWindow &window, sf::Transform drawableTransform, float delta)
{
    auto size = this->size();
    drawableTransform.translate(-(size.x * _anchor.x), -(size.y * _anchor.y)); 
    _frames[_curFrame]->Draw(window, drawableTransform, delta);
    Tick(delta);
}


void AnimatedDrawable::Tick(float delta)
{
    if (_duration != 0)
    {
        _timeUntilChange -= delta;
        if (_timeUntilChange <= 0)
        {
            _timeUntilChange += _duration;
            AdvanceFrame();
        }
    }
}

void AnimatedDrawable::AdvanceFrame()
{
    if (_loopOnce && IsFinished())
    {
        return;
    }

    _curFrame++;
    if (_curFrame == _frames.size())
    {
        ResetAnimation();
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
    archive(_loopOnce, "loopOnce");
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
    _frames.emplace_back(frame);
}

void AnimatedDrawable::RemoveFrame(const std::string & key)
{
    _frames.erase(alg::remove_if(_frames, [key](const std::unique_ptr<Drawable> & drawable) {
        return key == drawable->key();
    }));
}

void AnimatedDrawable::ResetAnimation() 
{
    _curFrame = 0;
}

bool AnimatedDrawable::IsFinished() 
{
    return _curFrame == _frames.size() - 1;
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

