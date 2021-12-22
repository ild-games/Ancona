#include <Ancona/HAL/SDL/VertexArrayImpl.hpp>

namespace ildhal
{

/* Pimpl Implementation */

/* HAL Interface Implementation */

VertexArray::VertexArray()
{
    _pimpl = std::make_unique<priv::VertexArrayImpl>();
}

VertexArray::VertexArray(PrimitiveRenderType type, std::size_t vertexCount)
{
    _pimpl = std::make_unique<priv::VertexArrayImpl>();
}

void VertexArray::SetVertexPosition(std::size_t index, const ild::Vector2f & newPosition)
{
}

void VertexArray::SetVertexTexCoords(std::size_t index, const ild::Vector2f & newTexCoords)
{
}

/* getters and setters */

priv::VertexArrayImpl & VertexArray::vertexArrayImpl() const
{
    return static_cast<priv::VertexArrayImpl &>(*_pimpl);
}

} // namespace ildhal
