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

void priv::VertexArrayImpl::Draw(
    SDL_Renderer & sdlRenderer,
    const ild::View & view,
    const ildhal::RenderStates & renderStates)
{
    SDL_Texture & texture = renderStates.renderStatesImpl().texture().textureImpl().sdlTexture();
    const ild::Transform & transform = renderStates.renderStatesImpl().transform();

    SDL_Vertex * transformedVertices = new SDL_Vertex[_numVertices];
    for (int i = 0; i < _numVertices; i++)
    {
        ild::Vector2f transformed = view.inverseTransform() * transform.transform() *
            ild::Vector2f(_vertices[i].position.x, _vertices[i].position.y);

        transformedVertices[i].position.x = transformed.x;
        transformedVertices[i].position.y = transformed.y;
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

void VertexArray::SetVertexTexCoords(int index, const ild::Vector2f & newTexCoords, const ild::Color & color)
{
    SDL_FPoint texCoord;
    texCoord.x = newTexCoords.x;
    texCoord.y = newTexCoords.y;

    SDL_Color sdlColor;
    sdlColor.r = color.r;
    sdlColor.g = color.g;
    sdlColor.b = color.b;
    sdlColor.a = color.a;

    vertexArrayImpl().vertices()[index].tex_coord = texCoord;
    vertexArrayImpl().vertices()[index].color = sdlColor;
}

void VertexArray::Draw(ildhal::RenderTarget & renderTarget, const ildhal::RenderStates & renderStates)
{
    vertexArrayImpl().Draw(
        renderTarget.renderTargetImpl().sdlRenderer(),
        renderTarget.renderTargetImpl().view(),
        renderStates);
}

/* getters and setters */

priv::VertexArrayImpl & VertexArray::vertexArrayImpl() const
{
    return static_cast<priv::VertexArrayImpl &>(*_pimpl);
}

} // namespace ildhal
