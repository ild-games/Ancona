#ifndef Ancona_HAL_SFML_SpriteImpl_H_
#define Ancona_HAL_SFML_SpriteImpl_H_

#include <SFML/Graphics.hpp>

#include <Ancona/HAL/Sprite.hpp>
#include <Ancona/HAL/SFML/DrawableImpl.hpp>

namespace ildhal
{

namespace priv
{

class SpriteImpl : public DrawableImpl
{
    public:
        SpriteImpl();

        SpriteImpl(
            const sf::Texture& texture,
            const sf::IntRect& rectangle);

        /* getters and setters */
        sf::Sprite & sfmlSprite() const;

};

}

}

#endif
