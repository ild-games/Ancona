#ifndef Ancona_Engine_Core_Systems_SpriteComponent_H_
#define Ancona_Engine_Core_Systems_SpriteComponent_H_

#include <Ancona/Engine/Core/Systems/Drawable/DrawableComponent.hpp>

namespace ild
{


/**
 * @brief Store state needed to draw an entity to the screen.
 *
 * @author Jeff Swenson
 */
class SpriteComponent : public DrawableComponent
{
    public:
        /**
         * @brief A component used to draw a sprite for an entity.
         *
         * @param positionComponent Component that defines the entity's position.
         * @param textureKey String that describes which texture should be used
         * @param priority RenderPriority that determines when the sprite is rendered
         * @param priorityOffset Optional offset to the render priority
         */
        SpriteComponent(
                const PositionComponent & positionComponent, 
                const std::string textureKey,
                const RenderPriorityEnum priority,
                int priorityOffset = 0);

        /**
         * @brief Draws the sprite to the window.  The position the sprite is drawn to will be the center
         *        of the sprite.
         *
         * @param window Window the sprite should be drawn to.
         */
        void Draw(sf::RenderWindow & window);

        /**
         * @brief Gets the size of the sprite's texture.
         *
         * @return Vector2u with dimensions of the sprite's texture.
         */
        sf::Vector2u GetSize();
    private:
        /**
         * @brief Sprite being drawn.
         */
        sf::Sprite * _sprite;
};

}
#endif
