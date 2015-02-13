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
                const BasePhysicsComponent & physicsComponent, 
                const std::string textureKey,
                const int priority,
                int priorityOffset = 0,
                sf::Vector2f positionOffset = sf::Vector2f(0.0f, 0.0f));

        /**
         * @brief Draws the sprite to the window.  The position the sprite is drawn to will be the center
         *        of the sprite.
         *
         * @param window Window the sprite should be drawn to.
         */
        virtual void Draw(sf::RenderWindow & window, float delta);

        /* getters and setters */
        sf::Vector2u GetSize();
        int GetAlpha();
        void SetAlpha(int alpha);
    protected:
        /**
         * @brief Sprite being drawn.
         */
        sf::Sprite * _sprite;
};

}
#endif
