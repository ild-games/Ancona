#ifndef Ancona_Engine_Core_Systems_Image_H_
#define Ancona_Engine_Core_Systems_Image_H_

#include <SFML/Graphics.hpp>

#include <Ancona/Framework/Serializing/Serializing.hpp>

namespace ild
{


/**
 * @brief 
 *
 * @author Tucker Lein
 */
class Image
{
    public:
        virtual void Draw(sf::RenderWindow & window, float delta) = 0;

        virtual void Serialize(Archive & arc);
        
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
        std::string _textureKey;
        sf::Vector2f _position;
        float _rotation;
        int _alpha = 255;
};


}

GENERATE_ABSTRACT_CLASS_CONSTRUCTOR(ild::Image);

#endif
