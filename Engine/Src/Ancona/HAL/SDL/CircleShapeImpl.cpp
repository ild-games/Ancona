#include <memory>

#include <Ancona/HAL/CircleShape.hpp>
#include <Ancona/HAL/SDL/CircleShapeImpl.hpp>

namespace ildhal
{

/* Pimpl Implementation */

/* HAL Interface Implementation */

CircleShape::CircleShape()
{
    _pimpl = std::make_unique<priv::CircleShapeImpl>();
}

void CircleShape::radius(float radius)
{
}

float CircleShape::radius() const
{
    return 0.0f;
}

priv::CircleShapeImpl & CircleShape::circleShapeImpl() const
{
    return static_cast<priv::CircleShapeImpl &>(*_pimpl);
}

} // namespace ildhal
