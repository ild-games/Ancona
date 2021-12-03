#ifndef Ancona_HAL_SFML_CircleShapeImpl_H_
#define Ancona_HAL_SFML_CircleShapeImpl_H_

#include <SFML/Graphics.hpp>

#include <Ancona/HAL/CircleShape.hpp>
#include <Ancona/HAL/SFML/ShapeImpl.hpp>

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

}

}

#endif
