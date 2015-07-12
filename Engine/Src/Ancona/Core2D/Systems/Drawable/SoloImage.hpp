#ifndef Ancona_Engine_Core_Systems_SoloImage_H_
#define Ancona_Engine_Core_Systems_SoloImage_H_

#include <memory>

#include <Ancona/Core2D/Systems/Drawable/Image.hpp>

namespace ild
{

/**
 * @brief 
 *
 * @author Tucker Lein
 */
class SoloImage : public Image
{
    public:
        void Draw(sf::RenderWindow & window, float delta);

        void SetupSprite();

        void Serialize(Archive & arc);

        /* getters and setters */
        virtual sf::Vector2u size();
    private:
        std::unique_ptr<sf::Sprite> _sprite;


};

}

#endif
