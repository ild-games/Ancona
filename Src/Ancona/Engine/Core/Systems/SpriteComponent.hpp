#ifndef Ancona_Engine_Core_Systems_SpriteComponent_H_
#define Ancona_Engine_Core_Systems_SpriteComponent_H_

#include <SFML/Graphics.hpp>

#include "PositionComponent.hpp"

namespace ild
{

/**
 * @brief Store state needed to draw an entity to the screen.
 *
 * @author Jeff Swenson
 */
class SpriteComponent 
{
    public:
        /**
         * @brief A component used to define the position for the entity.
         *
         * @param positionComponent Component that defines the entities position.
         * @param textureKey String that describes which texture should be used
         */
        SpriteComponent(
                PositionComponent & positionComponent, 
                const std::string textureKey);

        /**
         * @brief Draws the sprite to the window.  The position the sprite is drawn to will be the center
         * of the sprite.
         *
         * @param window Window the sprite should be drawn to.
         */
        void Draw(sf::RenderWindow & window);
    private:
        /**
         * @brief Component that defines the entities position.
         */
        PositionComponent & _positionComponent;
        /**
         * @brief Texture used by the sprite.
         */
        sf::Sprite _sprite; 
};

}
#endif
