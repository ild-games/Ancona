#include <Ancona/Engine/Core/Systems/Drawable/ShapeComponent.hpp>

using namespace ild;

ShapeComponent::ShapeComponent(
        const PositionComponent & positionComponent,
        sf::Shape & shape,
        const RenderPriorityEnum priorty,
        int priorityOffset) :
    DrawableComponent(
            positionComponent,
            priorty,
            priorityOffset),
    _shape(shape)
{
}

void ShapeComponent::Draw(sf::RenderWindow & window)
{

}

sf::Vector2u ShapeComponent::GetSize()
{
    return sf::Vector2u(
            _shape.getLocalBounds().width, 
            _shape.getLocalBounds().height);
}
