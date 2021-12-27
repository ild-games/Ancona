#include <Ancona/HAL/SDL/RenderStatesImpl.hpp>
#include <Ancona/HAL/SDL/RenderTargetImpl.hpp>
#include <Ancona/HAL/SDL/TextureImpl.hpp>
#include <Ancona/HAL/SDL/VertexArrayImpl.hpp>
#include <Ancona/System/Log.hpp>

namespace ildhal
{

/* Pimpl Implementation */
priv::VertexArrayImpl::VertexArrayImpl(int vertexCount) :
        _numVertices(vertexCount),
        _vertices(new SDL_Vertex[vertexCount])
{
}

priv::VertexArrayImpl::~VertexArrayImpl()
{
    delete[] _vertices;
}

void priv::VertexArrayImpl::Draw(SDL_Renderer & sdlRenderer, const ildhal::RenderStates & renderStates)
{
    SDL_Texture & texture = renderStates.renderStatesImpl().texture().textureImpl().sdlTexture();
    const ild::Transform & transform = renderStates.renderStatesImpl().transform();

    SDL_Vertex * transformedVertices = new SDL_Vertex[_numVertices];
    for (int i = 0; i < _numVertices; i++)
    {
        transformedVertices[i].position.x = _vertices[i].position.x + transform.position().x - _origin.x;
        transformedVertices[i].position.y = _vertices[i].position.y + transform.position().y - _origin.y;
        transformedVertices[i].color = _vertices[i].color;
        transformedVertices[i].tex_coord = _vertices[i].tex_coord;
    }

    if (SDL_RenderGeometry(&sdlRenderer, &texture, transformedVertices, _numVertices, nullptr, 0) != 0)
    {
        ILD_Log(std::string(SDL_GetError()));
    }
    delete[] transformedVertices;
}

/* HAL Interface Implementation */

VertexArray::VertexArray(PrimitiveRenderType type, int vertexCount)
{
    _pimpl = std::make_unique<priv::VertexArrayImpl>(vertexCount);
}

void VertexArray::SetVertexPosition(int index, const ild::Vector2f & newPosition)
{
    SDL_FPoint position;
    position.x = newPosition.x;
    position.y = newPosition.y;

    vertexArrayImpl().vertices()[index].position = position;
}

void VertexArray::SetVertexTexCoords(int index, const ild::Vector2f & newTexCoords)
{
    SDL_FPoint texCoord;
    texCoord.x = newTexCoords.x;
    texCoord.y = newTexCoords.y;

    SDL_Color color;
    color.r = 255;
    color.b = 255;
    color.g = 255;
    color.a = 255;

    vertexArrayImpl().vertices()[index].tex_coord = texCoord;
    vertexArrayImpl().vertices()[index].color = color;
}

void VertexArray::Draw(ildhal::RenderTarget & renderTarget, const ildhal::RenderStates & renderStates)
{
    vertexArrayImpl().Draw(renderTarget.renderTargetImpl().sdlRenderer(), renderStates);
}

/* getters and setters */

void VertexArray::origin(const ild::Vector2f & newOrigin)
{
    vertexArrayImpl().origin(newOrigin);
}

void VertexArray::origin(float x, float y)
{
    vertexArrayImpl().origin(ild::Vector2f(x, y));
}

priv::VertexArrayImpl & VertexArray::vertexArrayImpl() const
{
    return static_cast<priv::VertexArrayImpl &>(*_pimpl);
}

} // namespace ildhal
