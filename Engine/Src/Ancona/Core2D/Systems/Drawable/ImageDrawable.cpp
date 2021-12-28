#include <Ancona/Core2D/Systems/Drawable/ImageDrawable.hpp>
#include <Ancona/HAL.hpp>
#include <Ancona/Util2D/VectorMath.hpp>

REGISTER_POLYMORPHIC_SERIALIZER(ild::ImageDrawable);

namespace ild
{

ImageDrawable::ImageDrawable(std::string textureKey, const float priority, const std::string & key) :
        Drawable(priority, key),
        _textureKey(textureKey)
{
}

ImageDrawable::ImageDrawable(const float priority, const std::string & key) : Drawable(priority, key), _textureKey("")
{
}

Drawable * ImageDrawable::Copy()
{
    auto drawable = new ImageDrawable();
    Drawable::CopyProperties(drawable);
    drawable->textureKey(_textureKey);
    drawable->textureRect(_textureRect);
    drawable->tiledArea(_tiledArea);
    drawable->isTiled(_isTiled);
    drawable->isWholeImage(_isWholeImage);
    drawable->SetupDrawable();
    return drawable;
}

void ImageDrawable::OnDraw(ildhal::RenderTarget & target, Transform drawableTransform, float delta)
{
    if (!_vertexArray)
    {
        return;
    }

    ildhal::RenderStates states(ildhal::BlendAlpha, drawableTransform, *_texture);
    _vertexArray->Draw(target, states);
}

void ImageDrawable::SetupDrawable()
{
    if (_textureKey == "")
    {
        return;
    }

    SetupDrawable(ResourceLibrary::Get<ildhal::Texture>(_textureKey));
}

void ImageDrawable::SetupDrawable(ildhal::Texture * texture)
{
    _texture = texture;
    if (_isWholeImage)
    {
        _textureRect.Dimension.x = texture->size().x;
        _textureRect.Dimension.y = texture->size().y;
    }

    if (_isTiled)
    {
        SetupTiledVertexArray(texture);
    }
    else
    {
        SetupSpriteVertexArray(texture);
    }
}

void ImageDrawable::SetupSpriteVertexArray(ildhal::Texture * texture)
{
    _tileSize = Vector2f(
        _isWholeImage ? texture->size().x : _textureRect.Dimension.x,
        _isWholeImage ? texture->size().y : _textureRect.Dimension.y);
    _numTiles = Vector2f(1.0f, 1.0f);
    _numVertices = NUM_VERTICES_PER_TILE;
    _vertexArray.reset(new ildhal::VertexArray(ildhal::TriangleStrip, _numVertices));

    int vertexIndex = 0;
    AddVertexTile(0, 0, vertexIndex, true);
}

void ImageDrawable::SetupTiledVertexArray(ildhal::Texture * texture)
{
    _tileSize = Vector2f(
        _isWholeImage ? texture->size().x : _textureRect.Dimension.x,
        _isWholeImage ? texture->size().y : _textureRect.Dimension.y);

    _numTiles = Vector2f(_tiledArea.x / _tileSize.x, _tiledArea.y / _tileSize.y);
    _numVertices = std::ceil(_numTiles.x) * std::ceil(_numTiles.y) * NUM_VERTICES_PER_TILE;
    _vertexArray.reset(new ildhal::VertexArray(ildhal::TriangleStrip, _numVertices));

    SetupTiledVertexArrayTiles();
}

void ImageDrawable::SetupTiledVertexArrayTiles()
{
    int vertexIndex = 0;
    for (int whichYBlock = 0; whichYBlock < std::ceil(_numTiles.y); whichYBlock++)
    {
        // For every row in the vertex array, go the opposite direction as the last row. This lets the next
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

void ImageDrawable::AddVertexTile(int whichXBlock, int whichYBlock, int & vertexIndex, bool isLeftToRight)
{
    // First triangle
    VertexTileVert(0, whichXBlock, whichYBlock, vertexIndex, isLeftToRight);
    VertexTileVert(1, whichXBlock, whichYBlock, vertexIndex, isLeftToRight);
    VertexTileVert(2, whichXBlock, whichYBlock, vertexIndex, isLeftToRight);

    // Second triangle
    VertexTileVert(2, whichXBlock, whichYBlock, vertexIndex, isLeftToRight);
    VertexTileVert(1, whichXBlock, whichYBlock, vertexIndex, isLeftToRight);
    VertexTileVert(3, whichXBlock, whichYBlock, vertexIndex, isLeftToRight);
}

void ImageDrawable::VertexTileVert(
    int whichVertex,
    int whichXBlock,
    int whichYBlock,
    int & vertexIndex,
    bool isLeftToRight)
{
    float fractionPartX = whichXBlock < std::ceil(_numTiles.x) - 1 ? 0 : _numTiles.x - (int) _numTiles.x;
    float fractionPartY = whichYBlock < std::ceil(_numTiles.y) - 1 ? 0 : _numTiles.y - (int) _numTiles.y;
    int xVertexOffset = isLeftToRight ? (whichVertex < 2 ? 0 : 1) : (whichVertex < 2 ? 1 : 0);
    int yVertexOffset = (whichVertex + 1) % 2;

    float positionX = (whichXBlock * _tileSize.x) + (_tileSize.x * xVertexOffset);
    float positionY = (whichYBlock * _tileSize.y) + (_tileSize.y * yVertexOffset);
    positionX -= (fractionPartX > 0 && xVertexOffset == 1) ? _tileSize.x * (1.0f - fractionPartX) : 0;
    positionY -= (fractionPartY > 0 && yVertexOffset == 1) ? _tileSize.y * (1.0f - fractionPartY) : 0;

    _vertexArray->SetVertexPosition(vertexIndex, Vector2f(positionX, positionY));

    float texCoordsX = xVertexOffset * _tileSize.x + _textureRect.Position.x;
    float texCoordsY = yVertexOffset * _tileSize.y + _textureRect.Position.y;
    texCoordsX -= (fractionPartX > 0 && xVertexOffset == 1) ? _tileSize.x * (1.0f - fractionPartX) : 0;
    texCoordsY -= (fractionPartY > 0 && yVertexOffset == 1) ? _tileSize.y * (1.0f - fractionPartY) : 0;
    texCoordsX /= _texture->size().x;
    texCoordsY /= _texture->size().y;
    _vertexArray->SetVertexTexCoords(vertexIndex, Vector2f(texCoordsX, texCoordsY), _color);

    vertexIndex++;
}

void ImageDrawable::Serialize(Archive & arc)
{
    Drawable::Serialize(arc);
    arc(_textureKey, "textureKey");
    arc(_isWholeImage, "isWholeImage");
    arc(_textureRect, "textureRect");
    arc(_tiledArea, "tiledArea");
    arc(_isTiled, "isTiled");
}

void ImageDrawable::FetchDependencies(const Entity & entity)
{
    Drawable::FetchDependencies(entity);
    if (_textureKey != "")
    {
        SetupDrawable(ResourceLibrary::Get<ildhal::Texture>(_textureKey));
    }
}

/* getters and setters */
Vector2f ImageDrawable::size()
{
    if (_isTiled)
    {
        return VectorMath::ComponentMultiplication(_tiledArea, _scale);
    }
    else
    {
        return VectorMath::ComponentMultiplication(_textureRect.Dimension, _scale);
    }
}

void ImageDrawable::alpha(int newAlpha)
{
    _color.a = (unsigned char) newAlpha;
    SetupDrawable(_texture);
}

void ImageDrawable::color(Color newColor)
{
    _color = newColor;
    SetupDrawable(_texture);
}

} // namespace ild
