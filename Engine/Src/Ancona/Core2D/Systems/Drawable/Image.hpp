#ifndef Ancona_Engine_Core_Systems_Image_H_
#define Ancona_Engine_Core_Systems_Image_H_

#include <SFML/Graphics.hpp>

#include <Ancona/Framework/Serializing/Serializing.hpp>

namespace ild
{

/**
 * @brief An image is something drawn to the screen used by SpriteDrawable and AnimatedDrawable.
 *
 * @author Tucker Lein
 */
class Image
{
    public:
        /**
         * @brief Blank constructor needed for serializing.
         */
        Image() { }

        /**
         * @brief Constructs an image.
         *
         * @param textureKey Key for the texture.
         */
        Image(std::string textureKey);

        /**
         * @brief Draws the image to the window.
         *
         * @param window RenderWindow for the game.
         */
        virtual void Draw(sf::RenderWindow & window, float delta) = 0;

        /**
         * @copydoc ild::CameraComponent::Serialize
         */
        virtual void Serialize(Archive & arc);
        
        /**
         * @brief Sets up the sprite info, such as the origin point.
         */
        virtual void SetupSprite() = 0;

        /* getters and setters */
        void position(sf::Vector2f newPosition) { _position = newPosition; }
        sf::Vector2f position() { return _position; }
        void rotation(float newRotation) { _rotation = newRotation; }
        float rotation() { return _rotation; }
        int alpha() { return _alpha; }
        virtual void alpha(int newAlpha) { _alpha = newAlpha; }
        virtual sf::Vector2u size() = 0;

    protected:
        std::string _textureKey = "";
        sf::Vector2f _position;
        float _rotation;
        int _alpha = 255;
};


}

GENERATE_ABSTRACT_CLASS_CONSTRUCTOR(ild::Image);

#endif
