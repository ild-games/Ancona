#ifndef Ancona_Engine_Core_Systems_Drawable_DrawableComponet_H_
#define Ancona_Engine_Core_Systems_Drawable_DrawableComponet_H_

#include <memory>

#include <SFML/Graphics.hpp>

#include <Ancona/Engine/Core/Systems/Drawable/AnimatedDrawable.hpp>
#include <Ancona/Engine/Core/Systems/Drawable/Drawable.hpp>
#include <Ancona/Engine/Core/Systems/Drawable/ShapeDrawable.hpp>
#include <Ancona/Engine/Core/Systems/Drawable/SpriteDrawable.hpp>
#include <Ancona/Engine/Core/Systems/Drawable/TextDrawable.hpp>
#include <Ancona/Engine/Core/Systems/PositionComponent.hpp>

namespace ild
{

class DrawableSystem;

/**
 * @brief Component used to draw elements on an entity.
 *
 * @author Tucker Lein
 */
class DrawableComponent
{
    public:
        /**
         * @brief Construct a DrawableComponent.
         *
         * @param drawableSystem DrawableSystem for the screen.
         */
        DrawableComponent(
                DrawableSystem & drawableSystem,
                const PositionComponent & positionComponent);

        /**
         * @brief Adds a sprite drawable element to the component.
         *
         * @param key Key for the sprite element on the component.
         * @param textureKey Key that identifies the texture the sprite should use.
         * @param priority RenderPriority that handles when the sprite is drawn.
         * @param priorityOffset offset of priority, defaults to 0.
         * @param positionOffset Offset coordinates against the position of the DrawableComponent, defaults to {0, 0}
         *
         * @returns Pointer to the sprite element.
         */
        SpriteDrawable * AddSprite(
                const std::string key,
                const std::string textureKey,
                const RenderPriorityEnum priority,
                int priorityOffset = 0,
                sf::Vector2f positionOffset = sf::Vector2f(0.0f, 0.0f));

        /**
         * @brief Adds an animated drawable element to the component.
         *
         * @param key Key for the animated element on the component.
         * @param textureKey Key that identifies the texture the animated sprite should use.
         * @param priority RenderPriority that handles when the sprite is drawn.
         * @param frameDimensions Dimensions of a frame in the animated texture.
         * @param numFrames Number of frames in the animation.
         * @param duration Seconds per frame.
         * @param priorityOffset offset of priority, defaults to 0.
         * @param positionOffset Offset coordinates against the position of the DrawableComponent, defaults to {0, 0}
         *
         * @returns Pointer to the sprite element.
         */
        AnimatedDrawable * AddAnimation(
                const std::string key,
                const std::string textureKey,
                const RenderPriorityEnum priority,
                sf::Vector2f frameDimensions,
                int numFrames,
                float duration,
                int priorityOffset = 0,
                sf::Vector2f positionOffset = sf::Vector2f(0.0f, 0.0f));

        /**
         * @brief Adds a text drawable element to the component.
         *
         * @param key Key for the text element on the component.
         * @param text Text shown on the window.
         * @param fontKey Name of font to use.
         * @param color Color of font.
         * @param characterSize Size of font in pixels.
         * @param priority RenderPriority that handles when the text is drawn.
         * @param priorityOffset offset of priority, defaults to 0.
         * @param positionOffset Offset coordinates against the position of the DrawableComponent, defaults to {0, 0}
         * @param smooth Determines if the font is smooth or not, defaults to true.
         *
         * @returns Pointer to the text element.
         */
        TextDrawable * AddText(
                const std::string key,
                const std::string text,
                const std::string fontKey,
                const sf::Color color,
                const int characterSize,
                const RenderPriorityEnum priority,
                int priorityOffset = 0,
                sf::Vector2f positionOffset = sf::Vector2f(0.0f, 0.0f),
                bool smooth = true);

        /**
         * @brief Adds a shape drawable element to the component.
         *
         * @param key Key for the shape element on the component.
         * @param shape SFML shape to be drawn.
         * @param priority RenderPriority that handles when the text is drawn.
         * @param priorityOffset offset of priority, defaults to 0.
         * @param positionOffset Offset coordinates against the position of the DrawableComponent, defaults to {0, 0}
         *
         * @returns Pointer to the shape element.
         */
        ShapeDrawable * AddShape(
                const std::string key,
                sf::Shape & shape,
                const RenderPriorityEnum priority,
                int priorityOffset = 0,
                sf::Vector2f positionOffset = sf::Vector2f(0.0f, 0.0f));

        /**
         * @brief Removes a drawable from the component.
         *
         * @param key Key of the drawable.
         */
        void RemoveDrawable(const std::string key);


        /* getters and setters */
        std::vector<Drawable *> GetDrawables();
        Drawable * GetDrawable(std::string key) { return _drawables[key].get(); }
        template <class T> T * GetDrawable(std::string key) { return static_cast<T *>(_drawables[key].get()); } 
    private:
        /**
         * @brief Holds all the drawables the component controls.
         */
        std::map<std::string, std::unique_ptr<Drawable> > _drawables;
        /**
         * @brief DrawableSystem for the screen.
         */
        DrawableSystem & _drawableSystem;
        /**
         * @brief PositionComponent for the entity this drawable component is associated with.
         */
        const PositionComponent & _positionComponent;

};

}

#endif
