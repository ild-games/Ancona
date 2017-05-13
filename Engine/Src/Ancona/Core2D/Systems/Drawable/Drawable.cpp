#include <Ancona/Core2D/Systems/Drawable/Drawable.hpp>
#include <Ancona/Core2D/Systems/Drawable/DrawableSystem.hpp>

REGISTER_POLYMORPHIC_SERIALIZER_ABSTRACT_BASE(ild::Drawable);

using namespace ild;

Drawable::Drawable(
        const int priority,
        const std::string & key,
        int priorityOffset,
        sf::Vector2f anchor) :
    _key(key),
    _anchor(anchor),
    _renderPriority(priority),
    _priorityOffset(priorityOffset)
{

}

void Drawable::Serialize(Archive &arc)
{
    arc(_renderPriority,"renderPriority");
    arc(_priorityOffset,"priorityOffset");
    arc(_rotation,"rotation");
    arc(_scale,"scale");
    arc(_anchor,"anchor");
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
    transform.rotate(_rotation).scale(_scale);
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
    _scale.x = std::abs(_scale.x) * leftOrRightSignum;
}

void Drawable::SetYDirection(int upOrDownSignum)
{
    _scale.y = std::abs(_scale.y) * upOrDownSignum;
}

/* getters and setters */
sf::Vector2f Drawable::position(sf::Vector2f entityPosition)
{
    auto size = this->size();
    return entityPosition - sf::Vector2f(size.x * _anchor.x, size.y * _anchor.y);
}