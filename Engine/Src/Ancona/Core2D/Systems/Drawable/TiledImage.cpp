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

void TiledImage::Draw(sf::RenderWindow & window, float delta)
{
    for(int i = 0; i < _textureRects.size(); i++)
    {
        float newX = _position.x + _textureRects[i].second.left;
        float newY = _position.y + _textureRects[i].second.top;
        _sprites[i]->setPosition(newX, newY);
        _sprites[i]->setRotation(_rotation);
        window.draw(*_sprites[i]);
    }
}

void TiledImage::SetupSprite()
{
    sf::Texture & texture = *ResourceLibrary::Get<sf::Texture>(_textureKey);
    for(int i = 0; i < _textureRects.size(); i++)
    {
        _sprites.push_back(std::unique_ptr<sf::Sprite>(new sf::Sprite(texture)));
        auto curRect = _textureRects[i];
        _sprites[i]->setTextureRect(curRect.first);
        _sprites[i]->setOrigin(
                (curRect.second.width / 2),
                (curRect.second.height / 2));
    }
}

void TiledImage::Serialize(Archive & arc)
{
    Image::Serialize(arc);
    arc(_textureRects, "texture-rects");
}

/* getters and setters */
sf::Vector2u TiledImage::size()
{
    float maxWidth = 0, maxHeight = 0, curWidth, curHeight;
    for(auto & sprite : _sprites)
    {
        curWidth = sprite->getPosition().x + sprite->getLocalBounds().width > maxWidth;
        curHeight = sprite->getPosition().y + sprite->getLocalBounds().height > maxHeight;
        if(curWidth > maxWidth)
        {
            maxWidth = curWidth;
        }
        if(curHeight > maxHeight)
        {
            maxHeight = curHeight;
        }
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
