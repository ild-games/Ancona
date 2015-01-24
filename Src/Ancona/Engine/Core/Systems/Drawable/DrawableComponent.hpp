#ifndef Ancona_Engine_Core_Systems_DrawableComponent_H_
#define Ancona_Engine_Core_Systems_DrawableComponent_H_

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <Ancona/Engine/Core/Systems/PositionSystem.hpp>

namespace ild
{


namespace RenderPriority
{

    /**
     * @brief Determines when the drawable objects are rendered, the lower the priority the sooner they are rendered.
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
 * @brief Handles a drawable element.
 *
 * @author Tucker Lein
 */
class DrawableComponent
{

    public:
        /**
         * @brief Constructs a DrawableComponent.
         *
         * @param positionComponent PositionComponent that defines the entity's position.
         * @param priority RenderPriority that determines when the drawable obj is rendered.
         * @param priorityOffset Optional offset to the render priority.
         */
        DrawableComponent(
                const PositionComponent & positionComponent,
                const RenderPriorityEnum priority,
                int priorityOffset = 0);

        /**
         * @brief Draws the object to the window.
         *
         * @param window RenderWindow for the game.
         */
        virtual void Draw(sf::RenderWindow & window) = 0;

        /**
         * @brief Gets the size of the drawable object.
         *
         * @return Vector2u with dimensions of the drawable object.
         */
        virtual sf::Vector2u GetSize() = 0;


        /* getters and setters */
        RenderPriorityEnum GetRenderPriority() { return _renderPriority; }
        int GetPriorityOffset() { return _priorityOffset; }
        float GetRotation() { return _rotation; }
        void SetRotation(float rotation) { _rotation = rotation; }

    protected:
        /**
         * @brief Component that defines the entities position.
         */
        const PositionComponent & _positionComponent;
        /**
         * @brief SFML Drawable obj being drawn.
         */
        sf::Drawable * _drawable; 
        /**
         * @brief Priority of rendering this obj.
         */
        RenderPriorityEnum _renderPriority;
        /**
         * @brief Offsets the render priority.
         */
        int _priorityOffset;
        /**
         * @brief Amount to rotate the sprite
         */
        float _rotation;

};

}

#endif
