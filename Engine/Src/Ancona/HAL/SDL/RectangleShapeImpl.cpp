#include <memory>

#include <Ancona/HAL/SDL/RectangleShapeImpl.hpp>

namespace ildhal
{

/* Pimpl Implementation */

/* HAL Interface Implementation */

RectangleShape::RectangleShape()
{
    _pimpl = std::make_unique<priv::RectangleShapeImpl>();
}

RectangleShape::RectangleShape(const ild::Vector2f & size)
{
    _pimpl = std::make_unique<priv::RectangleShapeImpl>();
}

/* getters and setters */

const ild::Vector2f RectangleShape::size() const
{
    return ild::Vector2f(0.0f, 0.0f);
}

void RectangleShape::size(const ild::Vector2f & newSize)
{
}

priv::RectangleShapeImpl & RectangleShape::rectangleShapeImpl() const
{
    return static_cast<priv::RectangleShapeImpl &>(*_pimpl);
}

} // namespace ildhal
