#include <Ancona/HAL/SDL/ShapeImpl.hpp>

namespace ildhal
{

/* Pimpl Implementation */

/* HAL Interface Implementation */

/* getters and setters */
void Shape::origin(const ild::Vector2f & origin)
{
    // shapeImpl().origin(origin);
}

void Shape::origin(float x, float y)
{
    // shapeImpl().origin(ild::Vector2f(x, y));
}

const ild::Color Shape::fillColor() const
{
    return ild::Color::Black;
    // return shapeImpl().fillColor();
}

void Shape::fillColor(const ild::Color & color)
{
    // shapeImpl().fillColor(color);
}

const ild::Color Shape::outlineColor() const
{
    return ild::Color::Black;
    // return shapeImpl().outlineColor();
}

void Shape::outlineColor(const ild::Color & color)
{
    // shapeImpl().outlineColor(color);
}

priv::ShapeImpl & Shape::shapeImpl() const
{
    return static_cast<priv::ShapeImpl &>(*_pimpl);
}

} // namespace ildhal
