#ifndef Ancona_Engine_Core_Systems_ImageDrawable_H_
#define Ancona_Engine_Core_Systems_ImageDrawable_H_

#include <memory>

#include <Ancona/Core2D/Systems/Drawable/Drawable.hpp>

namespace ild
{

class ImageDrawable : public Drawable
{
    public:
        ImageDrawable() { }

        ImageDrawable(
                std::string textureKey,
                const int priority,
                const std::string & key);

        ImageDrawable(
                const int priority,
                const std::string & key);

        Drawable * Copy() override;

        void Serialize(Archive & arc) override;

        void FetchDependencies(const Entity & entity) override;

        void SetupSprite(sf::Texture * texture);
        void SetupSprite();

        /* getters and setters */
        sf::Vector2f size() override;
        void alpha(int newAlpha) override;
        int alpha() override { return _alpha; }
        sf::Color color() { return _color; }
        void color(sf::Color newColor);
        void isWholeImage(bool isWholeImage) { _isWholeImage = isWholeImage; }
        void isTiled(bool isTiled) { _isTiled = isTiled; }
        void tiledArea(const sf::Vector2f & tiledArea) { _tiledArea = tiledArea; }
        void textureKey(const std::string & textureKey) { _textureKey = textureKey; }
        void textureRect(const Box2 & textureRect) { _textureRect = textureRect; }
    private:
        std::string _textureKey;
        Box2 _textureRect;
        std::unique_ptr<sf::Sprite> _sprite;
        sf::Vector2f _tiledArea;
        sf::Color _color = sf::Color::White;
        int _alpha = 255;
        bool _isTiled = false;
        bool _isWholeImage = true;

        void OnDraw(sf::RenderWindow &window, sf::Transform transform, float delta) override;
        void ApplyAlpha();
        void ApplyColor();
};

}

#endif
