#include <Ancona/Core2D/Systems/Drawable/Drawable.hpp>
#include <Ancona/Core2D/Systems/Drawable/DrawableSystem.hpp>

REGISTER_POLYMORPHIC_SERIALIZER_ABSTRACT_BASE(ild::Drawable);

using namespace ild;

Drawable::Drawable(
        const int priority,
        int priorityOffset,
        sf::Vector2f positionOffset) :
    _positionOffset(positionOffset),
    _renderPriority(priority),
    _priorityOffset(priorityOffset)
{

}

void Drawable::Serialize(Archive &arc)
{
    arc.system(_drawableSystem, "drawable");
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
    OnDraw(window, parentTransform.combine(CalculateTransforms()), delta);
}

sf::Transform Drawable::CalculateTransforms()
{
    sf::Transform transform;
    transform.translate(_positionOffset).rotate(_rotation).scale(_scale);
    return transform;
}

void Drawable::FetchDependencies(const Entity & entity)
{
    _drawableComponent = _drawableSystem->at(entity);
    _drawableComponent->AddCachedDrawable(_key, this);
}

void Drawable::rotation(float newRotation)
{
    _rotation = newRotation;
}

void Drawable::scale(sf::Vector2f newScale)
{
    _scale = newScale;
}
