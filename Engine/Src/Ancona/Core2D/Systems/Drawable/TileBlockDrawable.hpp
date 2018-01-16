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
        void alpha(int newAlpha) { _alpha = newAlpha; }
        int alpha() override { return _alpha; }
    private:
        std::string _textureKey;
        sf::Vector2f _numTiles;
        sf::Vector2f _tileSize;
        sf::Vector2f _size;
        sf::VertexArray _vertexArray;
        sf::Texture * _texture;
        int _alpha = 255;

        void OnDraw(sf::RenderTarget & target, sf::Transform transform, float delta) override;
};

}

#endif
