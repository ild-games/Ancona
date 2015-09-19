#include <Ancona/Core2D/Systems/Drawable/ImageDrawable.hpp>

REGISTER_POLYMORPHIC_SERIALIZER(ild::ImageDrawable);

using namespace ild;

ImageDrawable::ImageDrawable(
        const int priority,
        int priorityOffset,
        sf::Vector2f positionOffset,
        std::string textureKey,
        sf::IntRect textureRect) :
    Drawable(
            priority,
            priorityOffset,
            positionOffset),
    _textureKey(textureKey),
    _textureRect(textureRect)
{
    SetupSprite();
}

void ImageDrawable::OnDraw(sf::RenderWindow &window, sf::Transform drawableTransform, float delta)
{
    sf::RenderStates states(drawableTransform);
    window.draw(*_sprite, states);
}

void ImageDrawable::SetupSprite()
{
    sf::Texture &texture = *ResourceLibrary::Get<sf::Texture>(_textureKey);
    _sprite.reset(new sf::Sprite(texture));

    if (_isWholeImage)
    {
        _sprite->setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
    }
    else
    {
        _sprite->setTextureRect(_textureRect);
        _sprite->setOrigin(_textureRect.width / 2, _textureRect.height / 2);
    }
}


void ImageDrawable::Serialize(Archive & arc)
{
    Drawable::Serialize(arc);
    arc(_textureKey, "textureKey");
    arc(_isWholeImage, "isWholeImage");
    arc(_textureRect, "textureRect");
}

void ImageDrawable::FetchDependencies(const Entity &entity)
{
    Drawable::FetchDependencies(entity);
    SetupSprite();
}

/* getters and setters */
sf::Vector2f ImageDrawable::size()
{
    float width, height;
    if (_isWholeImage)
    {
        sf::Texture &texture = *ResourceLibrary::Get<sf::Texture>(_textureKey);
        width = texture.getSize().x;
        height = texture.getSize().y;
    }
    else
    {
        width = _textureRect.width;
        height = _textureRect.height;
    }
    return sf::Vector2f(width * _scale.x, height * _scale.y);
}

void ImageDrawable::alpha(int newAlpha)
{
    sf::Color col(_sprite->getColor());
    col.a = newAlpha;
    _sprite->setColor(col);
}

int ImageDrawable::alpha()
{
    return _sprite->getColor().a;
}
