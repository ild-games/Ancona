#ifndef Ancona_Engine_Core_Systems_ShapeDrawable_H_
#define Ancona_Engine_Core_Systems_ShapeDrawable_H_

#include <Ancona/Engine/Core/Systems/Drawable/Drawable.hpp>
#include <SFML/Graphics.hpp>

namespace ild
{

/**
 * @brief Responsible for drawing a shape to the window
 *
 * @author Tucker Lein
 */
class ShapeDrawable : public Drawable
{
    public:
        /**
         * @brief An element to draw a shape to an entity.
         *
         * @param positionComponent Component that defines the entity's position.
         * @param shape SFML Shape that is going to be drawn.
         * @param priority RenderPriority that determines when the sprite is rendered
         * @param priorityOffset Optional offset to the render priority
         * @param positionOffset Offset coordinates from the PositionComponent
         */
        ShapeDrawable(
                const PositionComponent & positionComponent, 
                sf::Shape & shape,
                const RenderPriorityEnum priority,
                int priorityOffset,
                sf::Vector2f positionOffset = sf::Vector2f(0.0f, 0.0f),
                const std::string key = "");

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
