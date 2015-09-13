#include <Ancona/Core2D/Systems/Drawable/TiledImage.hpp>

REGISTER_POLYMORPHIC_SERIALIZER(ild::TiledImage)

using namespace ild;

TiledImage::TiledImage(
        std::string textureKey,
        std::vector<std::pair<sf::IntRect, sf::IntRect>> textureRects):
    Image(textureKey),
    _textureRects(textureRects)
{
}

void TiledImage::Draw(sf::RenderWindow & window, sf::Transform transform, float delta)
{
    for(int i = 0; i < _textureRects.size(); i++)
    {
        float newX = _position.x +
                (_textureRects[i].second.left + (_textureRects[i].second.width / 2.0f));
        float newY = _position.y +
                (_textureRects[i].second.top + (_textureRects[i].second.height / 2.0f));
        _sprites[i]->setPosition(newX, newY);
        sf::RenderStates states(transform);
        window.draw(*_sprites[i], states);
    }
}

void TiledImage::SetupSprite()
{
    sf::Texture &texture = *ResourceLibrary::Get<sf::Texture>(_textureKey);
    for (int i = 0; i < _textureRects.size(); i++)
    {
        _sprites.push_back(std::unique_ptr<sf::Sprite>(new sf::Sprite(texture)));
        auto curRect = _textureRects[i];
        _sprites[i]->setTextureRect(curRect.first);
        _sprites[i]->setOrigin(
                (((float) curRect.second.width) / 2),
                (((float) curRect.second.height) / 2));
    }
    SetupRectRotations();
    SetupRectScales();
}

void TiledImage::SetupRectRotations()
{
    for (auto it = _rectRotations.begin(); it != _rectRotations.end(); ++it)
    {
        int pos = std::stoi(it->first);
        float rectRotation = it->second;
        if (pos > 0 && pos < _sprites.size())
        {
            float newRotation = _sprites[pos]->getRotation() + rectRotation;
            _sprites[pos]->setRotation(newRotation);
        }
    }
}

void TiledImage::SetupRectScales()
{
    for (auto it = _rectScales.begin(); it != _rectScales.end(); ++it)
    {
        int pos = std::stoi(it->first);
        sf::Vector2f rectScale = it->second;
        if (pos > 0 && pos < _sprites.size())
        {
            sf::Vector2f spriteScale = _sprites[pos]->getScale();
            _sprites[pos]->setScale(spriteScale.x * rectScale.x, spriteScale.y * rectScale.y);
        }
    }
}
void TiledImage::Serialize(Archive & arc)
{
    Image::Serialize(arc);
    arc(_textureRects, "textureRects");
    arc(_rectRotations, "rectRotations");
    arc(_rectScales, "rectScales");
}

/* getters and setters */
sf::Vector2u TiledImage::size()
{
    float maxWidth = 0, maxHeight = 0, curWidth = 0, curHeight = 0;
    for(auto textureRect : _textureRects)
    {
        curWidth = textureRect.second.left + textureRect.second.width;
        curHeight = textureRect.second.top + textureRect.second.height;
        maxWidth = std::max(maxWidth, curWidth);
        maxHeight = std::max(maxHeight, curHeight);
    }
    return sf::Vector2u(maxWidth, maxHeight);
}

void TiledImage::alpha(int newAlpha)
{
    _alpha = newAlpha;    
    for(auto & sprite : _sprites)
    {
        sf::Color col(sprite->getColor());
        col.a = newAlpha;
        sprite->setColor(col);
    }
}

void TiledImage::rotation(float newRotation)
{
    for (auto & sprite : _sprites)
    {
        sprite->setRotation(newRotation);
    }
    SetupRectRotations();
}

void TiledImage::scale(sf::Vector2f newScale)
{
    for (auto & sprite : _sprites)
    {
        sprite->setScale(newScale);
    }
    SetupRectScales();
}
