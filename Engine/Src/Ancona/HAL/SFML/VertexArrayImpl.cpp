#include <Ancona/HAL/SFML/VertexArrayImpl.hpp>

namespace ildhal
{

/* Pimpl Implementation */
priv::VertexArrayImpl::VertexArrayImpl()
{
    _sfmlDrawable = std::make_unique<sf::VertexArray>();
}

priv::VertexArrayImpl::VertexArrayImpl(sf::PrimitiveType type, std::size_t vertexCount)
{
    _sfmlDrawable = std::make_unique<sf::VertexArray>(type, vertexCount);
}

sf::VertexArray & priv::VertexArrayImpl::sfmlVertexArray() const { return static_cast<sf::VertexArray &>(*_sfmlDrawable); }

/* HAL Interface Implementation */

VertexArray::VertexArray()
{
    _pimpl = std::make_unique<priv::VertexArrayImpl>();
}

VertexArray::VertexArray(PrimitiveRenderType type, std::size_t vertexCount)
{
    _pimpl = std::make_unique<priv::VertexArrayImpl>(
        (sf::PrimitiveType) type,
        vertexCount);
}

void VertexArray::SetVertexPosition(std::size_t index, const ild::Vector2f & newPosition)
{
    sf::Vertex & sfmlVertex = vertexArrayImpl().sfmlVertexArray()[index];
    sfmlVertex.position = sf::Vector2f(newPosition.x, newPosition.y);
}

void VertexArray::SetVertexTexCoords(std::size_t index, const ild::Vector2f & newTexCoords)
{
    sf::Vertex & sfmlVertex = vertexArrayImpl().sfmlVertexArray()[index];
    sfmlVertex.texCoords = sf::Vector2f(newTexCoords.x, newTexCoords.y);
}

/* getters and setters */

priv::VertexArrayImpl & VertexArray::vertexArrayImpl() const
{
    return static_cast<priv::VertexArrayImpl &>(*_pimpl);
}

}
