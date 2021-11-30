#ifndef Ancona_Engine_Core_Systems_TextDrawable_H_
#define Ancona_Engine_Core_Systems_TextDrawable_H_

#include <Ancona/Core2D/Systems/Drawable/Drawable.hpp>
#include <Ancona/Graphics/Transform.hpp>
#include <Ancona/Graphics/Color.hpp>
#include <Ancona/HAL.hpp>
#include <Ancona/Framework/Serializing/Serializing.hpp>
#include <Ancona/Util/Vector2.hpp>

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
        TextDrawable(const std::string & text, const std::string & fontKey);

        /**
         * @brief An element to draw text to an entity.
         *
         * @param positionSystem System that can be used to determine the entity's location.
         * @param text Text being drawn.
         * @param fontKey Name of font to use.
         * @param color Color of the text.
         * @param characterSize Font size in pixels.
         * @param priority RenderPriority that determines when the sprite is rendered.
         * @param priorityOffset Optional offset to the render priority, defaults to 0.
         * @param anchor Offset coordinates from the PositionComponent
         * @param smooth Optional bool to determine if the text should be smoothed, defaults to true.
         */
        TextDrawable(
            const std::string& text,
            const std::string& fontKey,
            const Color color,
            const int characterSize,
            const float priority,
            const std::string & key,
            float priorityOffset = 0,
            Vector2f anchor = Vector2f(0.0f, 0.0f),
            bool smooth = true);

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
        const std::string & text() { return _text->string(); }
        void text(const std::string& text, bool resetOrigin = true);
        Vector2f size() override;
        int alpha() override;
        void alpha(int alpha) override;
        Color color() { return _color; }
        void color(Color newColor) { _color = newColor; SetupText(); }
    private:
        std::unique_ptr<ildhal::Text> _text;
        std::string _fontKey = "";
        Color _color = Color::White;
        int _characterSize = 10;
        bool _smooth = true;


        void SetupText();
        void CenterOrigin();
        void OnDraw(ildhal::RenderTarget & target, Transform drawableTransform, float delta) override;
};

}

#endif
