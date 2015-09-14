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
    arc(_serializedRotation,"rotation");
    arc(_serializedScale,"scale");
    arc(_positionOffset,"positionOffset");
    arc(_inactive, "inactive");
    arc(_key, "key");
}

void Drawable::Draw(sf::RenderWindow &window, sf::Transform parentTransform, float delta)
{
    _dynamicTransform = sf::Transform();
    _dynamicTransform.translate(_positionOffset);
    _transform = _dynamicTransform.combine(_staticTransform);
}

void Drawable::FetchDependencies(const Entity & entity)
{
    _drawableComponent = _drawableSystem->at(entity);

    rotation(_serializedRotation);
    scale(_serializedScale);
}

void Drawable::rotation(float newRotation)
{
    _staticTransform.rotate(-_rotation);
    _rotation = newRotation;
    _staticTransform.rotate(newRotation);
}

void Drawable::scale(sf::Vector2f newScale)
{
    _staticTransform.scale(
            1 / _scale.x,
            1 / _scale.y);
    _scale = newScale;
    _staticTransform.scale(
            newScale.x,
            newScale.y);
}
