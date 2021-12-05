#include <Ancona/HAL/SFML/ShapeImpl.hpp>

namespace ildhal
{

/* Pimpl Implementation */

sf::Shape &priv::ShapeImpl::sfmlShape() const
{
    return static_cast<sf::Shape &>(*_sfmlDrawable);
}

/* HAL Interface Implementation */

/* getters and setters */
void Shape::origin(const ild::Vector2f &origin)
{
    shapeImpl().sfmlShape().setOrigin(sf::Vector2f(origin.x, origin.y));
}

void Shape::origin(float x, float y)
{
    shapeImpl().sfmlShape().setOrigin(x, y);
}

const ild::Color Shape::fillColor() const
{
    return ild::Color(shapeImpl().sfmlShape().getFillColor().toInteger());
}

void Shape::fillColor(const ild::Color &color)
{
    shapeImpl().sfmlShape().setFillColor(sf::Color(color.toInteger()));
}

const ild::Color Shape::outlineColor() const
{
    return ild::Color(shapeImpl().sfmlShape().getOutlineColor().toInteger());
}

void Shape::outlineColor(const ild::Color &color)
{
    shapeImpl().sfmlShape().setOutlineColor(sf::Color(color.toInteger()));
}

ild::FloatRect Shape::localBounds() const
{
    auto sfmlRect = shapeImpl().sfmlShape().getLocalBounds();
    return ild::FloatRect(sfmlRect.left, sfmlRect.top, sfmlRect.width, sfmlRect.height);
}

priv::ShapeImpl &Shape::shapeImpl() const
{
    return static_cast<priv::ShapeImpl &>(*_pimpl);
}

} // namespace ildhal
