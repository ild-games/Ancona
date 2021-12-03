#ifndef Ancona_Engine_Core_Systems_TileBlockDrawable_H_
#define Ancona_Engine_Core_Systems_TileBlockDrawable_H_

#include <memory>

#include <Ancona/Core2D/Systems/Drawable/Drawable.hpp>
#include <Ancona/Core2D/Systems/Drawable/ImageDrawable.hpp>
#include <Ancona/Graphics/Transform.hpp>
#include <Ancona/HAL.hpp>
#include <Ancona/Util/Vector2.hpp>

namespace ild
{

class TileBlockDrawable : public Drawable
{
  public:
    TileBlockDrawable()
    {
    }
    Drawable *Copy() override;

    void Serialize(Archive &arc) override;
    void FetchDependencies(const Entity &entity) override;
    void InitializeVertexArray();

    /* getters and setters */
    Vector2f size() override
    {
        return _size;
    }
    void size(const Vector2f &size)
    {
        _size = size;
    }
    void textureKey(const std::string &textureKey)
    {
        _textureKey = textureKey;
    }
    void alpha(int newAlpha) override
    {
        _alpha = newAlpha;
    }
    int alpha() override
    {
        return _alpha;
    }
    ildhal::VertexArray &vertexArray() const
    {
        return *_vertexArray;
    }

  private:
    std::string _textureKey;
    Vector2f _numTiles;
    Vector2f _tileSize;
    int _numVertices = 0;
    Vector2f _size;
    std::unique_ptr<ildhal::VertexArray> _vertexArray;
    ildhal::Texture *_texture;
    int _alpha = 255;

    void OnDraw(ildhal::RenderTarget &target, Transform transform, float delta) override;

    /* vertex block init */
    int NUM_VERTICES_PER_TILE = 4;
    Vector2i SINGLE_BLOCK_TILE_POS = Vector2i(3, 3);
    Vector2i HORIZONTAL_BLOCK_TILE_POS = Vector2i(0, 3);
    Vector2i VERTICAL_BLOCK_TILE_POS = Vector2i(3, 0);
    Vector2i FULL_BLOCK_TILE_POS = Vector2i(0, 0);
    void SetupVertexBlock();
    void AddVertexTile(int whichXBlock, int whichYBlock, int &vertexIndex, bool isLeftToRight);
    Vector2i &BlockTileStartingPosition();
    int XVertexOffset(bool isLeftToRight, int whichVertex);
    int XTileToUse(int whichXBlock);
    int YTileToUse(int whichYBlock);
};

} // namespace ild

#endif
