#include <memory>

#include <Ancona/HAL/CircleShape.hpp>
#include <Ancona/HAL/SFML/CircleShapeImpl.hpp>

namespace ildhal
{

/* Pimpl Implementation */

priv::CircleShapeImpl::CircleShapeImpl()
{
    _sfmlDrawable = std::make_unique<sf::CircleShape>();
}

sf::CircleShape &priv::CircleShapeImpl::sfmlCircleShape() const
{
    return static_cast<sf::CircleShape &>(*_sfmlDrawable);
}

/* HAL Interface Implementation */

CircleShape::CircleShape()
{
    _pimpl = std::make_unique<priv::CircleShapeImpl>();
}

void CircleShape::radius(float radius)
{
    circleShapeImpl().sfmlCircleShape().setRadius(radius);
}

float CircleShape::radius() const
{
    return circleShapeImpl().sfmlCircleShape().getRadius();
}

priv::CircleShapeImpl &CircleShape::circleShapeImpl() const
{
    return static_cast<priv::CircleShapeImpl &>(*_pimpl);
}

} // namespace ildhal
