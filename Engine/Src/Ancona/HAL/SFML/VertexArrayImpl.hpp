#ifndef Ancona_HAL_SFML_VertexArrayImpl_H_
#define Ancona_HAL_SFML_VertexArrayImpl_H_

#include <SFML/Graphics.hpp>

#include <Ancona/HAL/SFML/DrawableImpl.hpp>
#include <Ancona/HAL/VertexArray.hpp>

namespace ildhal
{

namespace priv
{

class VertexArrayImpl : public DrawableImpl
{
  public:
    VertexArrayImpl();
    VertexArrayImpl(sf::PrimitiveType type, std::size_t vertexCount);

    /* getters and setters */
    sf::VertexArray &sfmlVertexArray() const;
};

} // namespace priv

} // namespace ildhal

#endif
