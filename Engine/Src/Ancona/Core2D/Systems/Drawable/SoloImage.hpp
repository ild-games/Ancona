#ifndef Ancona_Engine_Core_Systems_SoloImage_H_
#define Ancona_Engine_Core_Systems_SoloImage_H_

#include <memory>

#include <Ancona/Core2D/Systems/Drawable/Image.hpp>

namespace ild
{

/**
 * @brief An image which utilizes the entire texture given to it.
 *
 * @author Tucker Lein
 */
class SoloImage : public Image
{
    public:
        /**
         * @brief Blank constructor needed for serializing.
         */
        SoloImage() { }

        /**
         * @brief Constructs a SoloImage
         *
         * @param textureKey Key for the texture.
         */
        SoloImage(std::string textureKey);

        /**
         * @copydoc ild::Image::Draw
         */
        void Draw(sf::RenderWindow & window, sf::Transform transform, float delta);

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
        void rotation(float newRotation) override;
        void scale(sf::Vector2f newScale) override;
    private:
        std::unique_ptr<sf::Sprite> _sprite;


};

}

#endif
