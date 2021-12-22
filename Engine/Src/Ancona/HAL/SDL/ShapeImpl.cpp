#include <Ancona/HAL/SDL/ShapeImpl.hpp>

namespace ildhal
{

/* Pimpl Implementation */

/* HAL Interface Implementation */

/* getters and setters */
void Shape::origin(const ild::Vector2f & origin)
{
}

void Shape::origin(float x, float y)
{
}

const ild::Color Shape::fillColor() const
{
    return ild::Color::Black;
}

void Shape::fillColor(const ild::Color & color)
{
}

const ild::Color Shape::outlineColor() const
{
    return ild::Color::Black;
}

void Shape::outlineColor(const ild::Color & color)
{
}

ild::FloatRect Shape::localBounds() const
{
    return ild::FloatRect(0.0f, 0.0f, 0.0f, 0.0f);
}

priv::ShapeImpl & Shape::shapeImpl() const
{
    return static_cast<priv::ShapeImpl &>(*_pimpl);
}

} // namespace ildhal
