#ifndef Ancona_Engine_Core_Systems_TextComponent_H_
#define Ancona_Engine_Core_Systems_TextComponent_H_

#include <Ancona/Engine/Core/Systems/Drawable/DrawableComponent.hpp>

namespace ild
{

/**
 * @brief Responsible for drawing text to the window.
 *
 * @author Tucker Lein
 */
class TextComponent : public DrawableComponent
{
    public:
        /**
         * @brief A component used to draw text for an entity.
         *
         * @param positionComponent Component that defines the entity's position.
         * @param text Text being drawn.
         * @param fontKey Name of font to use.
         * @param color SFML Color of the text.
         * @param characterSize Font size in pixels.
         * @param priority RenderPriority that determines when the sprite is rendered.
         * @param priorityOffset Optional offset to the render priority, defaults to 0.
         * @param smooth Optional bool to determine if the text should be smoothed, defaults to true.
         */
        TextComponent(
                const PositionComponent & positionComponent,
                const std::string text,
                const std::string fontKey,
                const sf::Color color,
                const int characterSize,
                const RenderPriorityEnum priority,
                int priorityOffset = 0,
                bool smooth = true);

        /**
         * @brief Draws the text to the window. The position
         *
         * @param window
         */
        void Draw(sf::RenderWindow & window);

        /**
         * @brief Gets the size of the text's texture.
         *
         * @return Vector2u with the dimensions of the text's texture.
         */
        sf::Vector2u GetSize();

        /* getters and setters */
        std::string GetText() { return _text->getString(); }
        void SetText(std::string text);
    private:
        /**
         * @brief Text being drawn.
         */
        sf::Text * _text;

        /**
         * @brief Sets the text's origin point to be its center.
         */
        void CenterOrigin();
};

}

#endif
