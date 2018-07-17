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
        void InitializeVertexArray();

        /* getters and setters */
        sf::Vector2f size() override { return _size; }
        void size(const sf::Vector2f & size) { _size = size; }
        void textureKey(const std::string & textureKey) { _textureKey = textureKey; }
        void alpha(int newAlpha) override { _alpha = newAlpha; }
        int alpha() override { return _alpha; }
    private:
        std::string _textureKey;
        sf::Vector2f _numTiles;
        sf::Vector2f _tileSize;
        int _numVertices = 0;
        sf::Vector2f _size;
        sf::VertexArray _vertexArray;
        sf::Texture * _texture;
        int _alpha = 255;

        void OnDraw(sf::RenderTarget & target, sf::Transform transform, float delta) override;

        /* vertex block init */
        int NUM_VERTICES_PER_TILE = 4;
        sf::Vector2i SINGLE_BLOCK_TILE_POS = sf::Vector2i(3, 3);
        sf::Vector2i HORIZONTAL_BLOCK_TILE_POS = sf::Vector2i(0, 3);
        sf::Vector2i VERTICAL_BLOCK_TILE_POS = sf::Vector2i(3, 0);
        sf::Vector2i FULL_BLOCK_TILE_POS = sf::Vector2i(0, 0);
        void SetupVertexBlock();
        void AddVertexTile(int whichXBlock, int whichYBlock, int & vertexIndex, bool isLeftToRight);
        sf::Vector2i & BlockTileStartingPosition();
        int XVertexOffset(bool isLeftToRight, int whichVertex);
        int XTileToUse(int whichXBlock);
        int YTileToUse(int whichYBlock);
};

}

#endif
