#ifndef Ancona_HAL_SFML_ShapeImpl_H_
#define Ancona_HAL_SFML_ShapeImpl_H_

#include <SFML/Graphics.hpp>

#include <Ancona/HAL/Shape.hpp>
#include <Ancona/HAL/SFML/DrawableImpl.hpp>

namespace ildhal
{

namespace priv
{

class ShapeImpl : public DrawableImpl
{
    public:
        /* getters and setters */
        sf::Shape & sfmlShape() const;

};

}

}

#endif
