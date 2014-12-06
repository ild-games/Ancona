#ifndef Ancona_Engine_Core_Systems_SpriteComponent_H_
#define Ancona_Engine_Core_Systems_SpriteComponent_H_

#include <SFML/Graphics.hpp>

#include "PositionComponent.hpp"
#include <iostream>

namespace ild
{

namespace RenderPriority
{

    /**
     * @brief Determines when the sprites are rendered, the lower the priority the sooner they are rendered.
     *
     * @author Tucker Lein
     */
    enum RenderPriority
    {
        Background = -1000,
        Player = 0,
        Foreground = 1000,
    };
}

/**
 * @brief Defines when the sprite should be rendered
 *
 * @author Tucker Lein
 */
typedef RenderPriority::RenderPriority RenderPriorityEnum;

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
         * @param priority RenderPriority that determines when the sprite is rendered
         * @param priorityOffset Optional offset to the render priority
         */
        SpriteComponent(
                PositionComponent & positionComponent, 
                const std::string textureKey,
                const RenderPriorityEnum priority,
                int priorityOffset = 0);

        /**
         * @brief Draws the sprite to the window.  The position the sprite is drawn to will be the center
         * of the sprite.
         *
         * @param window Window the sprite should be drawn to.
         */
        void Draw(sf::RenderWindow & window);

        /* getters and setters */
        float GetRotation();
        RenderPriorityEnum GetRenderPriority();
        int GetPriorityOffset();
        void SetRotation(float rotation);
        sf::Sprite * GetSprite();
    private:
        /**
         * @brief Component that defines the entities position.
         */
        PositionComponent & _positionComponent;
        /**
         * @brief Texture used by the sprite.
         */
        sf::Sprite _sprite; 
        /**
         * @brief Amount to rotate the sprite
         */
        float _rotation;

        /**
         * @brief Priority of rendering this sprite
         */
        RenderPriorityEnum _renderPriority;

        /**
         * @brief Offsets the render priority
         */
        int _priorityOffset;
};

}
#endif
