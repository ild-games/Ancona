#ifndef Ancona_Engine_Core_Systems_ShapeDrawable_H_
#define Ancona_Engine_Core_Systems_ShapeDrawable_H_

#include <SFML/Graphics.hpp>

#include <Ancona/Core2D/Systems/Drawable/Drawable.hpp>
#include <Ancona/Framework/Serializing/SerializingContext.hpp>


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
         * @brief Default constructor, should only be used by the serializer.
         */
        ShapeDrawable() {}

        /**
         * @brief An element to draw a shape to an entity.
         *
         * @param positionSystem System that defines the entity's position
         * @param shape SFML Shape that is going to be drawn.
         * @param priority RenderPriority that determines when the sprite is rendered
         * @param priorityOffset Optional offset to the render priority
         * @param anchor Offset coordinates from the PositionComponent
         */
        ShapeDrawable(
                sf::Shape * shape,
                const int priority,
                const std::string & key,
                int priorityOffset = 0,
                sf::Vector2f anchor = sf::Vector2f(0.0f, 0.0f));

        Drawable * Copy() override;

        /**
         * @copydoc ild::CameraComponent::Serialize
         */
        void Serialize(Archive & arc) override;

        /**
         * @copydoc ild::CameraComponent::FetchDependencies
         */
        void FetchDependencies(const Entity & entity) override;

        /* getters and setters */
        sf::Vector2f size() override;
        int alpha() override;
        void alpha(int alpha) override;

    private:
        /**
         * @brief Shape used for the drawing.
         */
        std::unique_ptr<sf::Shape> _shape;

        void OnDraw(sf::RenderWindow &window, sf::Transform drawableTransform, float delta) override;

};

}

#endif
