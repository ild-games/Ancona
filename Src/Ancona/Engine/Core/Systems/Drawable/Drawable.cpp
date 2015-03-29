#include <Ancona/Engine/Core/Systems/Drawable/Drawable.hpp>

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

void Drawable::Serialize(Archive &archive) {
    archive.system(_physicsSystem, "physics");
    archive(_renderPriority,"render-priority");
    archive(_priorityOffset,"priority-offset");
    archive(_rotation,"rotation");
    archive(_positionOffset,"position-offset");
}

void Drawable::FetchDependencies(const Entity & entity) {
    _physicsComponent = _physicsSystem->at(entity);
}

