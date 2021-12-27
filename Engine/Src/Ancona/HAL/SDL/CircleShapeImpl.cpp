#include <memory>

#include <Ancona/HAL/CircleShape.hpp>
#include <Ancona/HAL/SDL/CircleShapeImpl.hpp>
#include <Ancona/HAL/SDL/RenderStatesImpl.hpp>
#include <Ancona/HAL/SDL/RenderTargetImpl.hpp>

namespace ildhal
{

/* Pimpl Implementation */

void priv::CircleShapeImpl::Draw(SDL_Renderer & sdlRenderer, const ildhal::RenderStates & renderStates)
{
}

/* HAL Interface Implementation */

CircleShape::CircleShape()
{
    _pimpl = std::make_unique<priv::CircleShapeImpl>();
}

void CircleShape::Draw(ildhal::RenderTarget & renderTarget, const ildhal::RenderStates & renderStates)
{
    circleShapeImpl().Draw(renderTarget.renderTargetImpl().sdlRenderer(), renderStates);
}

/* getters and setters */

void CircleShape::radius(float radius)
{
}

float CircleShape::radius() const
{
    return 0.0f;
}

ild::FloatRect CircleShape::localBounds() const
{
    ild::FloatRect rect;
    return rect;
}

priv::CircleShapeImpl & CircleShape::circleShapeImpl() const
{
    return static_cast<priv::CircleShapeImpl &>(*_pimpl);
}

} // namespace ildhal
