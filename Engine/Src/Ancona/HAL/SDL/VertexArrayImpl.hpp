#pragma once

#include <SDL2/SDL.h>

#include <Ancona/Graphics/View.hpp>
#include <Ancona/HAL/SDL/DrawableImpl.hpp>
#include <Ancona/HAL/VertexArray.hpp>
#include <Ancona/Util/Vector2.hpp>

namespace ildhal
{

namespace priv
{

class VertexArrayImpl : public DrawableImpl
{
  public:
    VertexArrayImpl(int vertexCount);
    ~VertexArrayImpl();

    void Draw(SDL_Renderer & sdlRenderer, const ild::View & view, const ildhal::RenderStates & renderStates);

    /* getters and setters */
    SDL_Vertex * vertices() { return _vertices; }

  private:
    int _numVertices;
    SDL_Vertex * _vertices;
};

} // namespace priv

} // namespace ildhal
