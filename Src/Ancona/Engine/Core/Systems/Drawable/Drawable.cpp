#include <Ancona/Engine/Core/Systems/Drawable/Drawable.hpp>
#include <Ancona/Engine/Core/Systems/Drawable/DrawableSystem.hpp>

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
    arc(_renderPriority,"render-priority");
    arc(_priorityOffset,"priority-offset");
    arc(_rotation,"rotation");
    arc(_positionOffset,"position-offset");
    arc(_key, "key");
}

void Drawable::FetchDependencies(const Entity & entity)
{
    _physicsComponent = _physicsSystem->at(entity);
    _drawableComponent = _drawableSystem->at(entity);
    _drawableComponent->AddDrawable(_key, this);
}

