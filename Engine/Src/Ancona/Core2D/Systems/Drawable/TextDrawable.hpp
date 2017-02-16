#ifndef Ancona_Engine_Core_Systems_TextDrawable_H_
#define Ancona_Engine_Core_Systems_TextDrawable_H_

#include <Ancona/Core2D/Systems/Drawable/Drawable.hpp>
#include <Ancona/Framework/Serializing/Serializing.hpp>

namespace ild
{

/**
 * @brief Responsible for drawing text to the window.
 *
 * @author Tucker Lein
 */
class TextDrawable : public Drawable
{
    public:
        /**
         * @brief Default constructor, should only be used by the serializer.
         */
        TextDrawable() {}

        /**
         * @brief An element to draw text to an entity.
         *
         * @param positionSystem System that can be used to determine the entity's location.
         * @param text Text being drawn.
         * @param fontKey Name of font to use.
         * @param color SFML Color of the text.
         * @param characterSize Font size in pixels.
         * @param priority RenderPriority that determines when the sprite is rendered.
         * @param priorityOffset Optional offset to the render priority, defaults to 0.
         * @param anchor Offset coordinates from the PositionComponent
         * @param smooth Optional bool to determine if the text should be smoothed, defaults to true.
         */
        TextDrawable(
                const std::string text,
                const std::string fontKey,
                const sf::Color color,
                const int characterSize,
                const int priority,
                const std::string & key,
                int priorityOffset = 0,
                sf::Vector2f anchor = sf::Vector2f(0.0f, 0.0f),
                bool smooth = true);

        /**
         * @copydoc ild::CameraComponent::Serialize
         */
        void Serialize(Archive & arc) override;

        /**
         * @copydoc ild::CameraComponent::FetchDependencies
         */
        void FetchDependencies(const Entity & entity) override;

        /* getters and setters */
        std::string text() { return _text->getString(); }
        void text(std::string text);
        sf::Vector2f size() override;
        int alpha() override;
        void alpha(int alpha) override;
    private:
        std::unique_ptr<sf::Text> _text;

        void CenterOrigin();
        void OnDraw(sf::RenderWindow &window, sf::Transform drawableTransform, float delta) override;
};

}

#endif
