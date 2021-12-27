#pragma once

#include <SDL2/SDL.h>

#include <Ancona/HAL/RectangleShape.hpp>
#include <Ancona/HAL/RenderStates.hpp>
#include <Ancona/HAL/SDL/ShapeImpl.hpp>

namespace ildhal
{

namespace priv
{

class RectangleShapeImpl : public ShapeImpl
{
  public:
    RectangleShapeImpl(const ild::Vector2f & size = ild::Vector2f(0.0f, 0.0f));
    void Draw(SDL_Renderer & sdlRenderer, const ildhal::RenderStates & renderStates);

    /* getters and setters */
    const ild::Vector2f & size() const { return _size; }
    void size(const ild::Vector2f & newSize) { _size = newSize; }

  private:
    ild::Vector2f _size;
};

} // namespace priv

} // namespace ildhal
