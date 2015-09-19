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
        _textureRect.width = texture.getSize().x;
        _textureRect.height = texture.getSize().y;
    }

    _sprite->setTextureRect(_textureRect);
    _sprite->setOrigin(_textureRect.width / 2.0f, _textureRect.height / 2.0f);
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
    return sf::Vector2f(
            _textureRect.width * _scale.x,
            _textureRect.height * _scale.y);
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
