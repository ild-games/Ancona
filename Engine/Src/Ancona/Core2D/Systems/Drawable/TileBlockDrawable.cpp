#include <Ancona/Core2D/Systems/Drawable/TileBlockDrawable.hpp>
#include <Ancona/System/Log.hpp>

REGISTER_POLYMORPHIC_SERIALIZER(ild::TileBlockDrawable);

using namespace ild;

Drawable * TileBlockDrawable::Copy() {
    auto drawable = new TileBlockDrawable();
    Drawable::CopyProperties(drawable);
    drawable->textureKey(_textureKey);
    drawable->size(_size);
    drawable->InitializeVertexArray();
    return drawable;
}

void TileBlockDrawable::OnDraw(sf::RenderTarget & target, sf::Transform drawableTransform, float delta) {
    sf::RenderStates states;
    drawableTransform.translate(-(_tileSize.x * _numTiles.x * _anchor.x), -(_tileSize.y * _numTiles.y * _anchor.y));
    states.transform = drawableTransform;
    states.texture = _texture;
    target.draw(_vertexArray, states);
}

void TileBlockDrawable::Serialize(Archive & arc) {
    Drawable::Serialize(arc);
    arc(_textureKey, "textureKey");
    arc(_size, "size");
}

void TileBlockDrawable::FetchDependencies(const Entity &entity) {
    Drawable::FetchDependencies(entity);
    InitializeVertexArray();
}

void TileBlockDrawable::InitializeVertexArray() {
    if (_textureKey != "") {
        _texture = ResourceLibrary::Get<sf::Texture>(_textureKey);
        _tileSize = sf::Vector2f(_texture->getSize().x / 4, _texture->getSize().y / 4);
        _numTiles = sf::Vector2f(_size.x / _tileSize.x, _size.y / _tileSize.y);
        _numVertices = _numTiles.x * _numTiles.y * NUM_VERTICES_PER_TILE;
        //ILD_Log(std::ostringstream().flush() << "Tile size: " << _tileSize << ", Num tiles: " << _numTiles << ", Num vertices: " << _numVertices);

        SetupVertexBlock();
    }
}

void TileBlockDrawable::SetupVertexBlock() {
    _vertexArray = sf::VertexArray(sf::TrianglesStrip, _numVertices);
    sf::Vector2i & blockTileStartingPos = BlockTileStartingPosition();

    int vertexIndex = 0;
    for (int whichYBlock = 0; whichYBlock < (int)_numTiles.y; whichYBlock++) {
        for (int whichXBlock = 0; whichXBlock < (int)_numTiles.x; whichXBlock++) {
            for (int k = 0; k < NUM_VERTICES_PER_TILE; k++) {
                int xVertexOffset = k < 2 ? 0 : 1;
                int yVertexOffset = (k+1) % 2;
                int xTileToUse = XTileToUse(whichXBlock);
                int yTileToUse = YTileToUse(whichYBlock);

                float positionX = (whichXBlock * _tileSize.x) + (_tileSize.x * xVertexOffset);
                float positionY = (whichYBlock * _tileSize.y) + (_tileSize.y * yVertexOffset);
                //ILD_Log(std::ostringstream().flush() << "Vertex Index: " << vertexIndex);
                _vertexArray[vertexIndex].position = sf::Vector2f(positionX, positionY);

                float texCoordsX = (xTileToUse * _tileSize.x) + ((blockTileStartingPos.x + xVertexOffset) * _tileSize.x);
                float texCoordsY = (yTileToUse * _tileSize.y) + ((blockTileStartingPos.y + yVertexOffset) * _tileSize.y);
                _vertexArray[vertexIndex].texCoords = sf::Vector2f(texCoordsX, texCoordsY);

                vertexIndex++;
            }
        }
    }
}

sf::Vector2i & TileBlockDrawable::BlockTileStartingPosition() {
    if (_numTiles.x == 1.0f && _numTiles.y == 1.0f) {
        return SINGLE_BLOCK_TILE_POS;
    } else if (_numTiles.x > 1.0f && _numTiles.y == 1.0f) {
        return HORIZONTAL_BLOCK_TILE_POS;
    } else if (_numTiles.x == 1.0f && _numTiles.y > 1.0f) {
        return VERTICAL_BLOCK_TILE_POS;
    } else {
        return FULL_BLOCK_TILE_POS;
    }
}

int TileBlockDrawable::XTileToUse(int whichXBlock) {
    if (whichXBlock == 0) {
        return 0;
    } else if (whichXBlock > 0 && whichXBlock < _numTiles.x - 1) {
        return 1;
    } else {
        return 2;
    }
}

int TileBlockDrawable::YTileToUse(int whichYBlock) {
    if (whichYBlock == 0) {
        return 0;
    } else if (whichYBlock > 0 && whichYBlock < _numTiles.y - 1) {
        return 1;
    } else {
        return 2;
    }
}
