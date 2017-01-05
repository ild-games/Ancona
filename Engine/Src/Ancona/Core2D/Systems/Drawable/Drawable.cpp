#include <Ancona/Core2D/Systems/Drawable/Drawable.hpp>
#include <Ancona/Core2D/Systems/Drawable/DrawableSystem.hpp>

REGISTER_POLYMORPHIC_SERIALIZER_ABSTRACT_BASE(ild::Drawable);

using namespace ild;

Drawable::Drawable(
        const int priority,
        const std::string & key,
        int priorityOffset,
        sf::Vector2f positionOffset) :
    _positionOffset(positionOffset),
    _renderPriority(priority),
    _priorityOffset(priorityOffset),
    _key(key)
{

}

void Drawable::Serialize(Archive &arc)
{
    arc(_renderPriority,"renderPriority");
    arc(_priorityOffset,"priorityOffset");
    arc(_rotation,"rotation");
    arc(_scale,"scale");
    arc(_positionOffset,"positionOffset");
    arc(_inactive, "inactive");
    arc(_key, "key");
}

void Drawable::Draw(sf::RenderWindow &window, sf::Transform parentTransform, float delta)
{
    if (!_inactive) 
    {
        OnDraw(window, parentTransform.combine(CalculateTransforms()), delta);
    }
}

sf::Transform Drawable::CalculateTransforms()
{
    sf::Transform transform;
    transform.translate(_positionOffset).rotate(_rotation).scale(_scale);
    return transform;
}

void Drawable::FetchDependencies(const Entity & entity)
{
}

Drawable * Drawable::FindDrawable(const std::string &key)
{
    if (key == _key)
    {
        return this;
    }
    return nullptr;
}

void Drawable::SetXDirection(int leftOrRightSignum)
{
    if (_scale.x < 0)
    {
        _scale.x *= -1;
    }

    _scale.x *= leftOrRightSignum;
}

void Drawable::SetYDirection(int leftOrRightSignum)
{
    if (_scale.y < 0)
    {
        _scale.y *= -1;
    }

    _scale.y *= leftOrRightSignum;
}