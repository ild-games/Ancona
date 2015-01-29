#include <Ancona/Engine/Core/Systems/Drawable/ShapeDrawable.hpp>

using namespace ild;

ShapeDrawable::ShapeDrawable(
        const PositionComponent & positionComponent,
        sf::Shape & shape,
        const RenderPriorityEnum priorty,
        int priorityOffset,
        sf::Vector2f positionOffset,
        const std::string key) :
    Drawable(
            positionComponent,
            priorty,
            priorityOffset,
            positionOffset,
            key),
    _shape(shape)
{
}

void ShapeDrawable::Draw(sf::RenderWindow & window)
{
    sf::Vector2f position = sf::Vector2f(
            _positionComponent.Position.x + _positionOffset.x,
            _positionComponent.Position.y + _positionOffset.y);
    _shape.setPosition(position.x, position.y);
    _shape.setRotation(_rotation);
    window.draw(_shape);
}

sf::Vector2u ShapeDrawable::GetSize()
{
    return sf::Vector2u(
            _shape.getLocalBounds().width, 
            _shape.getLocalBounds().height);
}
