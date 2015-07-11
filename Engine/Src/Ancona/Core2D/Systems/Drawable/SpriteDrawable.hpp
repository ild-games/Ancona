#ifndef Ancona_Engine_Core_Systems_SpriteDrawable_H_
#define Ancona_Engine_Core_Systems_SpriteDrawable_H_

#include <memory>

#include <SFML/Graphics.hpp>

#include <Ancona/Core2D/Systems/Drawable/Drawable.hpp>

namespace ild
{


/**
 * @brief Responsible for drawing a sprite to the window.
 *
 * @author Jeff Swenson, Tucker Lein
 */
class SpriteDrawable : public Drawable
{
    public:
        /**
         * @brief Default constructor, should only be used by the serializer.
         */
        SpriteDrawable() {}

        /**
         * @brief An element to draw a sprite to an entity.
         *
         * @param physicsSystem System that describes the entity's location.
         * @param textureKey String that describes which texture should be used
         * @param priority RenderPriority that determines when the sprite is rendered
         * @param textureRects Optional list of IntRect pairs that describe the "tiles"
         *        the SpriteDrawable is made up of. The first IntRect is the location
         *        and width of the tile on the src texture, and the second IntRect is the
         *        location and width of the tile on the destination sprite. Defaults to
         *        empty, in this case the entire texture is used for the sprite without
         *        any tiling system.
         * @param priorityOffset Optional offset to the render priority
         * @param positionOffset Offset coordinates from the PositionComponent
         */
        SpriteDrawable(
                BasePhysicsSystem * physicsSystem,
                const std::string textureKey,
                const int priority,
                const std::vector<std::pair<sf::IntRect, sf::IntRect>> textureRects = std::vector<std::pair<sf::IntRect, sf::IntRect>>(),
                int priorityOffset = 0,
                sf::Vector2f positionOffset = sf::Vector2f(0.0f, 0.0f));

        /**
         * @brief Draws the sprite to the window.  The position the sprite is drawn to will be the center
         *        of the sprite.
         *
         * @param window Window the sprite should be drawn to.
         */
        virtual void Draw(sf::RenderWindow & window, float delta);

        /**
         * @copydoc ild::CameraComponent::Serialize
         */
        void Serialize(Archive & arc);

        /**
         * @copydoc ild::CameraComponent::FetchDependencies
         */
        void FetchDependencies(const Entity & entity);

        /* getters and setters */
        sf::Vector2u size();
        int alpha() { return _alpha; }
        void alpha(int alpha);
    protected:
        std::unique_ptr<sf::Sprite> _sprite;
        std::vector<std::unique_ptr<sf::Sprite>> _sprites;
        std::vector<std::pair<sf::IntRect, sf::IntRect>> _textureRects;
        std::string _textureKey;
        int _alpha = 255;

        bool IsWholeTexture();
};

}
#endif
