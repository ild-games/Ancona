#ifndef Ancona_Engine_Core_Systems_SpriteDrawable_H_
#define Ancona_Engine_Core_Systems_SpriteDrawable_H_

#include <Ancona/Engine/Core/Systems/Drawable/Drawable.hpp>

namespace ild
{


/**
 * @brief Responsible for drawing a sprite to the window.
 *
 * @author Jeff Swenson, Tucker Lein
 */
class SpriteDrawable : public Drawable
{
    public:
        /**
         * @brief An element to draw a sprite to an entity.
         *
         * @param positionComponent Component that defines the entity's position.
         * @param textureKey String that describes which texture should be used
         * @param priority RenderPriority that determines when the sprite is rendered
         * @param priorityOffset Optional offset to the render priority
         * @param positionOffset Offset coordinates from the PositionComponent
         */
        SpriteDrawable(
                const PositionComponent & positionComponent, 
                const std::string textureKey,
                const RenderPriorityEnum priority,
                int priorityOffset = 0,
                sf::Vector2f positionOffset = sf::Vector2f(0.0f, 0.0f),
                const std::string key = "");

        /**
         * @brief Draws the sprite to the window.  The position the sprite is drawn to will be the center
         *        of the sprite.
         *
         * @param window Window the sprite should be drawn to.
         */
        void Draw(sf::RenderWindow & window);

        /* getters and setters */
        sf::Vector2u GetSize();
        int GetAlpha();
        void SetAlpha(int alpha);
    private:
        /**
         * @brief Sprite being drawn.
         */
        sf::Sprite * _sprite;
};

}
#endif
