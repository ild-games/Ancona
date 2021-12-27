#pragma once

#include <Ancona/HAL/CircleShape.hpp>
#include <Ancona/HAL/RenderStates.hpp>
#include <Ancona/HAL/SDL/ShapeImpl.hpp>

namespace ildhal
{

namespace priv
{

class CircleShapeImpl : public ShapeImpl
{
  public:
    void Draw(SDL_Renderer & sdlRenderer, const ildhal::RenderStates & renderStates);
};

} // namespace priv

} // namespace ildhal
