#ifndef Ancona_Engine_Core_Systems_ShapeDrawable_H_
#define Ancona_Engine_Core_Systems_ShapeDrawable_H_

#include <jsoncpp/json/json.h>
#include <SFML/Graphics.hpp>

#include <Ancona/Engine/Core/Systems/Drawable/Drawable.hpp>
#include <Ancona/Engine/Loading/LoadingContext.hpp>


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
                const BasePhysicsComponent & physicsComponent, 
                sf::Shape & shape,
                const int priority,
                int priorityOffset,
                sf::Vector2f positionOffset = sf::Vector2f(0.0f, 0.0f));

        /**
         * @brief Draws the shape to the window.  The position the shape is drawn to will be the center
         *        of the sprite.
         *
         * @param window Window the shape should be drawn to.
         */
        void Draw(sf::RenderWindow & window, float delta);

        /**
         * @brief Inflate a shape drawable.
         */
        static void * Inflate(
                const Json::Value & object,
                const Entity entity,
                LoadingContext * loadingContext);

        /* getters and setters */
        sf::Vector2u GetSize();
        int GetAlpha();
        void SetAlpha(int alpha);
    private:
        /**
         * @brief Shape used for the drawing.
         */
        sf::Shape & _shape;
};

}

#endif
