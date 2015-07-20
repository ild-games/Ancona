#ifndef Ancona_Engine_Core_Systems_TiledImage_H_
#define Ancona_Engine_Core_Systems_TiledImage_H_

#include <memory>

#include <Ancona/Core2D/Systems/Drawable/Image.hpp>

namespace ild
{

/**
 * @brief An image which is made up of various tiles from a single texture.
 *
 * @author Tucker Lein
 */
class TiledImage : public Image
{
    public:
        /**
         * @brief Blank constructor needed for serializing.
         */
        TiledImage() { }

        /**
         * @brief Constructs a TiledImage
         *
         * @param textureKey Key for the texture
         * @param textureRects Optional list of IntRect pairs that describe the "tiles"
         *        the SpriteDrawable is made up of. The first IntRect is the location
         *        and width of the tile on the src texture, and the second IntRect is the
         *        location and width of the tile on the destination sprite. Defaults to
         *        empty, in this case the entire texture is used for the sprite without
         *        any tiling system.
         */
        TiledImage(
                std::string textureKey,
                std::vector<std::pair<sf::IntRect, sf::IntRect>> textureRects);

        /**
         * @copydoc ild::Image::Draw
         */
        void Draw(sf::RenderWindow & window, float delta);

        /**
         * @copydoc ild::Image::SetupSprite
         */
        void SetupSprite();

        /**
         * @copydoc ild::CameraComponent::Serialize
         */
        void Serialize(Archive & arc);

        /* getters and setters */
        virtual sf::Vector2u size();
        virtual void alpha(int newAlpha);
    private:
        std::vector<std::unique_ptr<sf::Sprite>> _sprites;
        /**
         * @brief List of pairs of IntRects that describe the tiles making up the image.
         *        The first IntRect is the location and width of the tile on the src 
         *        texture, and the second IntRect is the location and width of the tile 
         *        on the destination sprite. Defaults to empty, in this case the entire 
         *        texture is used for the sprite without any tiling system.
         */
        std::vector<std::pair<sf::IntRect, sf::IntRect>> _textureRects;
};

}

#endif
