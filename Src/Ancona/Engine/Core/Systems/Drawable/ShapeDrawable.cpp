#include <Ancona/Engine/Core/Systems/Drawable/ShapeDrawable.hpp>

using namespace ild;

ShapeDrawable::ShapeDrawable(
        const PositionComponent & positionComponent,
        sf::Shape & shape,
        const RenderPriorityEnum priorty,
        int priorityOffset,
        sf::Vector2f positionOffset) :
    Drawable(
            positionComponent,
            priorty,
            priorityOffset,
            positionOffset),
    _shape(shape)
{
    _shape.setOrigin(
            _shape.getLocalBounds().width / 2, 
            _shape.getLocalBounds().height / 2);
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

int ShapeDrawable::GetAlpha()
{
    return _shape.getFillColor().a;
}

void ShapeDrawable::SetAlpha(int alpha)
{
    sf::Color * outlineCol = 
        new sf::Color(_shape.getOutlineColor());
    outlineCol->a = alpha;
    _shape.setOutlineColor(*outlineCol);

    sf::Color * fillCol = 
        new sf::Color(_shape.getFillColor());
    fillCol->a = alpha;
    _shape.setFillColor(*fillCol);

    delete outlineCol;
    delete fillCol;
}
