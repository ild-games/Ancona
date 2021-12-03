#include <cmath>

#include <Ancona/Core2D/Systems/Drawable/TileBlockDrawable.hpp>
#include <Ancona/HAL.hpp>
#include <Ancona/System/Log.hpp>

REGISTER_POLYMORPHIC_SERIALIZER(ild::TileBlockDrawable);

using namespace ild;

Drawable *TileBlockDrawable::Copy()
{
    auto drawable = new TileBlockDrawable();
    Drawable::CopyProperties(drawable);
    drawable->textureKey(_textureKey);
    drawable->size(_size);
    drawable->InitializeVertexArray();
    return drawable;
}

void TileBlockDrawable::OnDraw(ildhal::RenderTarget &target, Transform drawableTransform, float delta)
{
    // std::string * hello = nullptr;
    // ILD_Log(*hello);
    drawableTransform.Translate(-(_tileSize.x * _numTiles.x * _anchor.x), -(_tileSize.y * _numTiles.y * _anchor.y));
    ildhal::RenderStates states(ildhal::BlendAlpha, drawableTransform, *_texture);
    target.Draw(*_vertexArray, states);
}

void TileBlockDrawable::Serialize(Archive &arc)
{
    Drawable::Serialize(arc);
    arc(_textureKey, "textureKey");
    arc(_size, "size");
}

void TileBlockDrawable::FetchDependencies(const Entity &entity)
{
    Drawable::FetchDependencies(entity);
    InitializeVertexArray();
}

void TileBlockDrawable::InitializeVertexArray()
{
    if (_textureKey != "")
    {
        _texture = ResourceLibrary::Get<ildhal::Texture>(_textureKey);
        _tileSize = Vector2f(_texture->size().x / 4, _texture->size().y / 4);
        _numTiles = Vector2f(_size.x / _tileSize.x, _size.y / _tileSize.y);
        _numVertices = std::ceil(_numTiles.x) * std::ceil(_numTiles.y) * NUM_VERTICES_PER_TILE;
        SetupVertexBlock();
    }
}

void TileBlockDrawable::SetupVertexBlock()
{
    _vertexArray = std::make_unique<ildhal::VertexArray>(ildhal::TriangleStrip, _numVertices);

    int vertexIndex = 0;
    for (int whichYBlock = 0; whichYBlock < std::ceil(_numTiles.y); whichYBlock++)
    {
        // For every row in the 9 slice, go the opposite direction as the last row. This lets the next
        // vertex process always be right next to the last vertex process which prevents tearing.
        if (whichYBlock % 2 == 0)
        {
            for (int whichXBlock = 0; whichXBlock < std::ceil(_numTiles.x); whichXBlock++)
            {
                AddVertexTile(whichXBlock, whichYBlock, vertexIndex, true);
            }
        }
        else
        {
            for (int whichXBlock = std::ceil(_numTiles.x) - 1; whichXBlock >= 0; whichXBlock--)
            {
                AddVertexTile(whichXBlock, whichYBlock, vertexIndex, false);
            }
        }
    }
}

void TileBlockDrawable::AddVertexTile(int whichXBlock, int whichYBlock, int &vertexIndex, bool isLeftToRight)
{
    for (int whichVertex = 0; whichVertex < NUM_VERTICES_PER_TILE; whichVertex++)
    {
        float fractionPartX = whichXBlock < std::ceil(_numTiles.x) - 1 ? 0 : _numTiles.x - (int)_numTiles.x;
        float fractionPartY = whichYBlock < std::ceil(_numTiles.y) - 1 ? 0 : _numTiles.y - (int)_numTiles.y;
        int xVertexOffset = XVertexOffset(isLeftToRight, whichVertex);
        int yVertexOffset = (whichVertex + 1) % 2;
        int xTileToUse = XTileToUse(whichXBlock);
        int yTileToUse = YTileToUse(whichYBlock);

        float positionX = (whichXBlock * _tileSize.x) + (_tileSize.x * xVertexOffset) - (_tileSize.x * fractionPartX);
        float positionY = (whichYBlock * _tileSize.y) + (_tileSize.y * yVertexOffset) - (_tileSize.y * fractionPartY);
        _vertexArray->SetVertexPosition(vertexIndex, Vector2f(positionX, positionY));

        float texCoordsX = (xTileToUse * _tileSize.x) + ((BlockTileStartingPosition().x + xVertexOffset) * _tileSize.x);
        float texCoordsY = (yTileToUse * _tileSize.y) + ((BlockTileStartingPosition().y + yVertexOffset) * _tileSize.y);
        _vertexArray->SetVertexTexCoords(vertexIndex, Vector2f(texCoordsX, texCoordsY));

        vertexIndex++;
    }
}

Vector2i &TileBlockDrawable::BlockTileStartingPosition()
{
    if (_numTiles.x == 1.0f && _numTiles.y == 1.0f)
    {
        return SINGLE_BLOCK_TILE_POS;
    }
    else if (_numTiles.x > 1.0f && _numTiles.y == 1.0f)
    {
        return HORIZONTAL_BLOCK_TILE_POS;
    }
    else if (_numTiles.x == 1.0f && _numTiles.y > 1.0f)
    {
        return VERTICAL_BLOCK_TILE_POS;
    }
    else
    {
        return FULL_BLOCK_TILE_POS;
    }
}

int TileBlockDrawable::XVertexOffset(bool isLeftToRight, int whichVertex)
{
    if (isLeftToRight)
    {
        if (whichVertex < 2)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    else
    {
        if (whichVertex < 2)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

int TileBlockDrawable::XTileToUse(int whichXBlock)
{
    if (whichXBlock == 0)
    {
        return 0;
    }
    else if (whichXBlock > 0 && whichXBlock < _numTiles.x - 1)
    {
        return 1;
    }
    else
    {
        return 2;
    }
}

int TileBlockDrawable::YTileToUse(int whichYBlock)
{
    if (whichYBlock == 0)
    {
        return 0;
    }
    else if (whichYBlock > 0 && whichYBlock < _numTiles.y - 1)
    {
        return 1;
    }
    else
    {
        return 2;
    }
}
