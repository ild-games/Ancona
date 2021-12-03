#ifndef Ancona_HAL_SFML_DrawableImpl_H_
#define Ancona_HAL_SFML_DrawableImpl_H_

#include <SFML/Graphics.hpp>

#include <Ancona/HAL/Drawable.hpp>

namespace ildhal
{

namespace priv
{

class DrawableImpl
{
    public:

        /* getters and setters */
        sf::Drawable & sfmlDrawable() const { return *_sfmlDrawable; }

    protected:
        std::unique_ptr<sf::Drawable> _sfmlDrawable;
};

}

}

#endif
