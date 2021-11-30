#ifndef Ancona_Engine_Core_Systems_ImageDrawable_H_
#define Ancona_Engine_Core_Systems_ImageDrawable_H_

#include <memory>

#include <Ancona/Core2D/Systems/Drawable/Drawable.hpp>
#include <Ancona/Graphics/Color.hpp>
#include <Ancona/Graphics/Transform.hpp>
#include <Ancona/HAL.hpp>
#include <Ancona/Util/Vector2.hpp>

namespace ild
{

class ImageDrawable : public Drawable
{
    public:
        ImageDrawable() { }

        ImageDrawable(
                std::string textureKey,
                const float priority,
                const std::string & key);

        ImageDrawable(
                const float priority,
                const std::string & key);

        Drawable * Copy() override;

        void Serialize(Archive & arc) override;

        void FetchDependencies(const Entity & entity) override;

        void SetupSprite(ildhal::Texture * texture);
        void SetupSprite();

        /* getters and setters */
        Vector2f size() override;
        void alpha(int newAlpha) override;
        int alpha() override { return _alpha; }
        Color color() { return _color; }
        void color(Color newColor);
        void isWholeImage(bool isWholeImage) { _isWholeImage = isWholeImage; }
        void isTiled(bool isTiled) { _isTiled = isTiled; }
        void tiledArea(const Vector2f & tiledArea) { _tiledArea = tiledArea; }
        void textureKey(const std::string & textureKey) { _textureKey = textureKey; }
        const std::string & textureKey() { return _textureKey; }
        void textureRect(const Box2 & textureRect) { _textureRect = textureRect; }
    private:
        std::string _textureKey;
        Box2 _textureRect;
        std::unique_ptr<ildhal::Sprite> _sprite;
        Vector2f _tiledArea;
        Color _color = Color::White;
        int _alpha = 255;
        bool _isTiled = false;
        bool _isWholeImage = true;

        void OnDraw(ildhal::RenderTarget & target, Transform transform, float delta) override;
        void ApplyAlpha();
        void ApplyColor();
};

}

#endif
