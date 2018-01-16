#include <Ancona/Core2D/Systems/Drawable/TileBlockDrawable.hpp>
#include <Ancona/System/Log.hpp>

REGISTER_POLYMORPHIC_SERIALIZER(ild::TileBlockDrawable);

using namespace ild;

Drawable * TileBlockDrawable::Copy() {
    auto drawable = new TileBlockDrawable();
    Drawable::CopyProperties(drawable);
    drawable->textureKey(_textureKey);
    drawable->size(_size);
    drawable->InitializeImages();
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
    InitializeImages();
}

void TileBlockDrawable::InitializeImages() {
    _vertexArray = sf::VertexArray(sf::TrianglesStrip, 4);
    if (_textureKey != "") {
        _texture = ResourceLibrary::Get<sf::Texture>(_textureKey);
        _tileSize = sf::Vector2f(_texture->getSize().x / 4, _texture->getSize().y / 4);
        _numTiles = sf::Vector2f(_size.x / _tileSize.x, _size.y / _tileSize.y);
        ILD_Log(std::ostringstream().flush() << "Tile size: " << _tileSize << ", Num tiles: " << _numTiles);

        if (_numTiles.x == 1.0f && _numTiles.y == 1.0f) {
            _vertexArray[0].position = sf::Vector2f(0, 0);
            _vertexArray[1].position = sf::Vector2f(0, _tileSize.y);
            _vertexArray[2].position = sf::Vector2f(_tileSize.x, 0);
            _vertexArray[3].position = sf::Vector2f(_tileSize.x, _tileSize.y);
            _vertexArray[0].texCoords = sf::Vector2f(_tileSize.x * 3, _tileSize.y * 3);
            _vertexArray[1].texCoords = sf::Vector2f(_tileSize.x * 3, _tileSize.y * 4);
            _vertexArray[2].texCoords = sf::Vector2f(_tileSize.x * 4, _tileSize.y * 3);
            _vertexArray[3].texCoords = sf::Vector2f(_tileSize.x * 4, _tileSize.y * 4);
        }

    }
}
