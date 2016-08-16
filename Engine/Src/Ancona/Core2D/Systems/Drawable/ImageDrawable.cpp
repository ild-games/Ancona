#include <Ancona/Core2D/Systems/Drawable/ImageDrawable.hpp>
#include <Ancona/Util2D/VectorMath.hpp>

REGISTER_POLYMORPHIC_SERIALIZER(ild::ImageDrawable);

using namespace ild;

ImageDrawable::ImageDrawable(
        std::string textureKey,
        const int priority,
        const std::string & key,
        bool isWholeImage,
        Box2 textureRect,
        int priorityOffset,
        sf::Vector2f positionOffset) :
    Drawable(
            priority,
            key,
            priorityOffset,
            positionOffset),
    _textureKey(textureKey),
    _textureRect(textureRect),
    _isWholeImage(isWholeImage)
{
}

ImageDrawable::ImageDrawable(
        sf::Texture * texture,
        const int priority,
        const std::string & key,
        bool isWholeImage,
        Box2 textureRect,
        int priorityOffset,
        sf::Vector2f positionOffset) :
    Drawable(
            priority,
            key,
            priorityOffset,
            positionOffset),
    _textureKey(""),
    _textureRect(textureRect),
    _texture(texture),
    _isWholeImage(isWholeImage)
{
}

void ImageDrawable::OnDraw(sf::RenderWindow &window, sf::Transform drawableTransform, float delta)
{
    sf::RenderStates states(drawableTransform);
    window.draw(*_sprite, states);
}

void ImageDrawable::SetupSprite()
{
    if (_textureKey != "")
    {
        _texture = ResourceLibrary::Get<sf::Texture>(_textureKey);
    }
    _sprite.reset(new sf::Sprite(*_texture));

    if (_isWholeImage)
    {
        _textureRect.Dimension.x = _texture->getSize().x;
        _textureRect.Dimension.y = _texture->getSize().y;
    }

    _sprite->setTextureRect(sf::IntRect(
        _textureRect.Position.x,
        _textureRect.Position.y,
        _textureRect.Dimension.x,
        _textureRect.Dimension.y));
    _sprite->setOrigin(_textureRect.Dimension.x / 2.0f, _textureRect.Dimension.y / 2.0f);
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
    return VectorMath::ComponentMultiplication(_textureRect.Dimension, _scale);
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
