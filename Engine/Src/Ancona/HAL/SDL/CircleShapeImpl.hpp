#ifndef Ancona_HAL_SFML_CircleShapeImpl_H_
#define Ancona_HAL_SFML_CircleShapeImpl_H_

#include <SFML/Graphics.hpp>

#include <Ancona/HAL/CircleShape.hpp>
#include <Ancona/HAL/SDL/ShapeImpl.hpp>

namespace ildhal
{

namespace priv
{

class CircleShapeImpl : public ShapeImpl
{
  public:
    CircleShapeImpl();

    /* getters and setters */
    sf::CircleShape & sfmlCircleShape() const;
};

} // namespace priv

} // namespace ildhal

#endif
