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
    arc(_rotation,"rotation");
    arc(_scale,"scale");
    arc(_positionOffset,"positionOffset");
    arc(_inactive, "inactive");
    arc(_key, "key");
}

void Drawable::FetchDependencies(const Entity & entity)
{
    _physicsComponent = _physicsSystem->at(entity);
    _drawableComponent = _drawableSystem->at(entity);
    _drawableComponent->AddDrawable(_key, this);
    rotation(_rotation);
    scale(_scale);
}
