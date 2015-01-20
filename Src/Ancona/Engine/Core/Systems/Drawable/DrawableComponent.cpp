#include <Ancona/Engine/Core/Systems/Drawable/DrawableComponent.hpp>

using namespace ild;

DrawableComponent::DrawableComponent(
        const PositionComponent & positionComponent,
        const RenderPriorityEnum priority,
        int priorityOffset) :
    _positionComponent(positionComponent),
    _renderPriority(priority),
    _priorityOffset(priorityOffset)
{
}
