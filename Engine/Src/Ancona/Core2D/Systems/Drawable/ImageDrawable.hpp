#pragma once

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
    ImageDrawable() {}

    ImageDrawable(std::string textureKey, const float priority, const std::string & key);

    ImageDrawable(const float priority, const std::string & key);

    Drawable * Copy() override;

    void Serialize(Archive & arc) override;

    void FetchDependencies(const Entity & entity) override;

    void SetupDrawable();
    void SetupDrawable(ildhal::Texture * texture);

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
    ildhal::Texture * _texture;
    Box2 _textureRect;
    std::unique_ptr<ildhal::VertexArray> _vertexArray;
    std::unique_ptr<ildhal::Sprite> _sprite;
    Color _color = Color::White;
    int _alpha = 255;
    bool _isWholeImage = true;

    bool _isTiled = false;
    Vector2f _tileSize;
    Vector2f _numTiles;
    int _numVertices = 0;
    Vector2f _tiledArea;
    const int NUM_VERTICES_PER_TILE = 6;

    void OnDraw(ildhal::RenderTarget & target, Transform transform, float delta) override;
    void SetupSprite(ildhal::Texture * texture);
    void SetupVertexArray(ildhal::Texture * texture);
    void SetupVertexArrayTiles();
    void AddVertexTile(int whichXBlock, int whichYBlock, int & vertexIndex, bool isLeftToRight);
    void VertexTileVert(int whichVertex, int whichXBlock, int whichYBlock, int & vertexIndex, bool isLeftToRight);
    void ApplyAlpha();
    void ApplyColor();
};

} // namespace ild
