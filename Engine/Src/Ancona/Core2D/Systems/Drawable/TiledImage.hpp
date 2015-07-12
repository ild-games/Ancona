#ifndef Ancona_Engine_Core_Systems_TiledImage_H_
#define Ancona_Engine_Core_Systems_TiledImage_H_

#include <memory>

#include <Ancona/Core2D/Systems/Drawable/Image.hpp>

namespace ild
{

/**
 * @brief 
 *
 * @author Tucker Lein
 */
class TiledImage : public Image
{
    public:
        void Draw(sf::RenderWindow & window, float delta);

        void SetupSprite();

        void Serialize(Archive & arc);

        /* getters and setters */
        virtual sf::Vector2u size();
        virtual void alpha(int newAlpha);
    private:
        std::vector<std::unique_ptr<sf::Sprite>> _sprites;
        std::vector<std::pair<sf::IntRect, sf::IntRect>> _textureRects;
};

}

#endif
