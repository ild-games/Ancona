#ifndef Ancona_HAL_SFML_RectangleShapeImpl_H_
#define Ancona_HAL_SFML_RectangleShapeImpl_H_

#include <SFML/Graphics.hpp>

#include <Ancona/HAL/RectangleShape.hpp>
#include <Ancona/HAL/SFML/ShapeImpl.hpp>

namespace ildhal
{

namespace priv
{

class RectangleShapeImpl : public ShapeImpl
{
    public:
        RectangleShapeImpl();
        explicit RectangleShapeImpl(const sf::Vector2f& size);

        /* getters and setters */
        sf::RectangleShape & sfmlRectangleShape() const;

};

}

}

#endif
