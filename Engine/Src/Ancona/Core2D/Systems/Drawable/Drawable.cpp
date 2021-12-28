#include <cmath>

#include <Ancona/Core2D/Systems/Drawable/Drawable.hpp>
#include <Ancona/Core2D/Systems/Drawable/DrawableSystem.hpp>

REGISTER_POLYMORPHIC_SERIALIZER_ABSTRACT_BASE(ild::Drawable);

using namespace ild;

Drawable::Drawable(const float priority, const std::string & key, float priorityOffset, Vector2f anchor) :
        _key(key),
        _anchor(anchor),
        _renderPriority(priority),
        _priorityOffset(priorityOffset)
{
}

void Drawable::CopyProperties(Drawable * drawable)
{
    drawable->key(_key);
    drawable->anchor(_anchor);
    drawable->renderPriority(_renderPriority);
    drawable->priorityOffset(_priorityOffset);
    drawable->scale(_scale);
    drawable->rotation(_rotation);
    drawable->inactive(_inactive);
    drawable->_direction = _direction;
}

void Drawable::Serialize(Archive & arc)
{
    arc(_renderPriority, "renderPriority");
    arc(_priorityOffset, "priorityOffset");
    arc(_rotation, "rotation");
    arc(_scale, "scale");
    arc(_anchor, "anchor");
    arc(_inactive, "inactive");
    arc(_key, "key");

    _direction.x = _scale.x < 0.0f ? -1 : 1;
    _direction.y = _scale.y < 0.0f ? -1 : 1;
}

void Drawable::Draw(ildhal::RenderTarget & target, Transform parentTransform, float delta)
{
    if (_inactive)
    {
        return;
    }

    Transform drawableTransform = parentTransform.Combine(CalculateTransforms());
    OnDraw(target, drawableTransform, delta);
}

Transform Drawable::CalculateTransforms()
{
    Transform transform;
    transform.rotation(_rotation);
    transform.scale(_scale);
    Vector2f drawableSize = size();
    transform.origin(_anchor.x * drawableSize.x, _anchor.y * drawableSize.y);
    return transform;
}

void Drawable::FetchDependencies(const Entity & entity)
{
}

Drawable * Drawable::FindDrawable(const std::string & key)
{
    if (key == _key)
    {
        return this;
    }
    return nullptr;
}

void Drawable::SetXDirection(int leftOrRightSignum)
{
    _direction.x = leftOrRightSignum;
    _scale.x = std::abs(_scale.x) * leftOrRightSignum;
}

void Drawable::SetYDirection(int upOrDownSignum)
{
    _direction.y = upOrDownSignum;
    _scale.y = std::abs(_scale.y) * upOrDownSignum;
}

/* getters and setters */
Vector2f Drawable::position(Vector2f entityPosition)
{
    auto size = this->size();
    return entityPosition - Vector2f(size.x * _anchor.x, size.y * _anchor.y);
}
