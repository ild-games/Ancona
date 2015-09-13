#include <Ancona/Core2D/Systems/Drawable/Drawable.hpp>
#include <Ancona/Core2D/Systems/Drawable/DrawableSystem.hpp>

REGISTER_POLYMORPHIC_SERIALIZER_ABSTRACT_BASE(ild::Drawable);

using namespace ild;

Drawable::Drawable(
        BasePhysicsSystem * physicsSystem,
        const int priority,
        int priorityOffset,
        sf::Vector2f positionOffset) :
    _physicsSystem(physicsSystem),
    _positionOffset(positionOffset),
    _renderPriority(priority),
    _priorityOffset(priorityOffset)
{

}

void Drawable::Serialize(Archive &arc)
{
    arc.system(_physicsSystem, "physics");
    arc.system(_drawableSystem, "drawable");
    arc(_renderPriority,"renderPriority");
    arc(_priorityOffset,"priorityOffset");
    arc(_serializedRotation,"rotation");
    arc(_serializedScale,"scale");
    arc(_positionOffset,"positionOffset");
    arc(_inactive, "inactive");
    arc(_key, "key");
}

void Drawable::FetchDependencies(const Entity & entity)
{
    _physicsComponent = _physicsSystem->at(entity);
    _drawableComponent = _drawableSystem->at(entity);
    _drawableComponent->AddDrawable(_key, this);

    rotation(_serializedRotation);
    scale(_serializedScale);
}

void Drawable::rotation(float newRotation)
{
    _transform.rotate(
            -_rotation,
            _physicsComponent->GetInfo().position().x + _positionOffset.x,
            _physicsComponent->GetInfo().position().y + _positionOffset.y);
    _rotation = newRotation;
    _transform.rotate(
            newRotation,
            _physicsComponent->GetInfo().position().x + _positionOffset.x,
            _physicsComponent->GetInfo().position().y + _positionOffset.y);
}

void Drawable::scale(sf::Vector2f newScale)
{
    _transform.scale(
            1 / _scale.x,
            1 /_scale.y,
            _physicsComponent->GetInfo().position().x + _positionOffset.x,
            _physicsComponent->GetInfo().position().y + _positionOffset.y);
    _scale = newScale;
    _transform.scale(
            newScale.x,
            newScale.y,
            _physicsComponent->GetInfo().position().x + _positionOffset.x,
            _physicsComponent->GetInfo().position().y + _positionOffset.y);
}
