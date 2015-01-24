#ifndef Ancona_Engine_Core_Systems_ShapeComponent_H_
#define Ancona_Engine_Core_Systems_ShapeComponent_H_

#include <Ancona/Engine/Core/Systems/Drawable/DrawableComponent.hpp>
#include <SFML/Graphics.hpp>

namespace ild
{

/**
 * @brief Component used to draw a shape.
 *
 * @author Tucker Lein
 */
class ShapeComponent : public DrawableComponent
{
    public:
        /**
         * @brief A component used to draw a shape for an entity.
         *
         * @param positionComponent Component that defines the entity's position.
         * @param shape SFML Shape that is going to be drawn.
         * @param priority RenderPriority that determines when the sprite is rendered
         * @param priorityOffset Optional offset to the render priority
         */
        ShapeComponent(
                const PositionComponent & positionComponent, 
                sf::Shape & shape,
                const RenderPriorityEnum priority,
                int priorityOffset = 0);

        /**
         * @brief Draws the shape to the window.  The position the shape is drawn to will be the center
         *        of the sprite.
         *
         * @param window Window the shape should be drawn to.
         */
        void Draw(sf::RenderWindow & window);

        /**
         * @brief Gets the size of the shape.
         *
         * @return Vector2u with dimensions of the shape.
         */
        sf::Vector2u GetSize();
    private:
        /**
         * @brief Shape used for the drawing.
         */
        sf::Shape & _shape;
};

}

#endif
