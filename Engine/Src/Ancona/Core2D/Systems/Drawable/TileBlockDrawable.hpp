#ifndef Ancona_Engine_Core_Systems_TileBlockDrawable_H_
#define Ancona_Engine_Core_Systems_TileBlockDrawable_H_

#include <memory>

#include <Ancona/Core2D/Systems/Drawable/Drawable.hpp>
#include <Ancona/Core2D/Systems/Drawable/ImageDrawable.hpp>

namespace ild
{

class TileBlockDrawable : public Drawable
{
    public:
        TileBlockDrawable() { }
        Drawable * Copy() override;

        void Serialize(Archive & arc) override;
        void FetchDependencies(const Entity & entity) override;
        void InitializeImages();

        /* getters and setters */
        sf::Vector2f size() override { return _size; }
        void size(const sf::Vector2f & size) { _size = size; }
        void textureKey(const std::string & textureKey) { _textureKey = textureKey; }
        void alpha(int newAlpha) override;
        int alpha() override;
    private:
        std::string _textureKey;
        sf::Vector2f _numTiles;
        sf::Vector2f _tileSize;
        sf::Vector2f _size;
        std::vector<std::unique_ptr<ImageDrawable>> _imageDrawables;
        std::vector<sf::Texture *> _baseTextures;

        void OnDraw(sf::RenderWindow &window, sf::Transform transform, float delta) override;
        void SetupImages(sf::Image image);

        ImageDrawable * topLeftDrawable(sf::Image image);
        ImageDrawable * topRightDrawable(sf::Image image);
        ImageDrawable * bottomLeftDrawable(sf::Image image);
        ImageDrawable * bottomRightDrawable(sf::Image image);
        ImageDrawable * topDrawable(sf::Image image);
        ImageDrawable * bottomDrawable(sf::Image image);
        ImageDrawable * leftDrawable(sf::Image image);
        ImageDrawable * rightDrawable(sf::Image image);
        ImageDrawable * centerDrawable(sf::Image image);
        ImageDrawable * topCapDrawable(sf::Image image);
        ImageDrawable * bottomCapDrawable(sf::Image image);
        ImageDrawable * leftCapDrawable(sf::Image image);
        ImageDrawable * rightCapDrawable(sf::Image image);
        ImageDrawable * verticalCenterDrawable(sf::Image image);
        ImageDrawable * horizontalCenterDrawable(sf::Image image);
        ImageDrawable * singleDrawable(sf::Image image);
};

}

#endif