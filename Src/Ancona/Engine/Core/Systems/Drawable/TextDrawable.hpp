#ifndef Ancona_Engine_Core_Systems_TextDrawable_H_
#define Ancona_Engine_Core_Systems_TextDrawable_H_

#include <Ancona/Engine/Core/Systems/Drawable/Drawable.hpp>

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
         * @brief An element to draw text to an entity.
         *
         * @param positionComponent Component that defines the entity's position.
         * @param text Text being drawn.
         * @param fontKey Name of font to use.
         * @param color SFML Color of the text.
         * @param characterSize Font size in pixels.
         * @param priority RenderPriority that determines when the sprite is rendered.
         * @param priorityOffset Optional offset to the render priority, defaults to 0.
         * @param positionOffset Offset coordinates from the PositionComponent
         * @param smooth Optional bool to determine if the text should be smoothed, defaults to true.
         */
        TextDrawable(
                const PositionComponent & positionComponent,
                const std::string text,
                const std::string fontKey,
                const sf::Color color,
                const int characterSize,
                const RenderPriorityEnum priority,
                int priorityOffset = 0,
                sf::Vector2f positionOffset = sf::Vector2f(0.0f, 0.0f),
                bool smooth = true);

        /**
         * @brief Draws the text to the window. The position
         *
         * @param window
         */
        void Draw(sf::RenderWindow & window);

        /* getters and setters */
        std::string GetText() { return _text->getString(); }
        void SetText(std::string text);
        sf::Vector2u GetSize();
        int GetAlpha();
        void SetAlpha(int alpha);
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
