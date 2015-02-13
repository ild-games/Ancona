#include <Ancona/Engine/Core/Systems/Drawable/Drawable.hpp>

using namespace ild;

Drawable::Drawable(
        const BasePhysicsComponent & physicsComponent,
        const int priority,
        int priorityOffset,
        sf::Vector2f positionOffset) :
    _physicsComponent(physicsComponent),
    _renderPriority(priority),
    _priorityOffset(priorityOffset),
    _positionOffset(positionOffset)
{
}
