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
        sf::Vector2f anchor) :
    Drawable(
            priority,
            key,
            priorityOffset,
            anchor),
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
        sf::Vector2f anchor) :
    Drawable(
            priority,
            key,
            priorityOffset,
            anchor),
    _textureKey(""),
    _textureRect(textureRect),
    _isWholeImage(isWholeImage)
{
    SetupSprite(texture);
}

void ImageDrawable::OnDraw(sf::RenderWindow &window, sf::Transform drawableTransform, float delta)
{
    if (_sprite.get() != NULL)
    {
        sf::RenderStates states(drawableTransform);
        window.draw(*_sprite, states);
    }
}

void ImageDrawable::SetupSprite(sf::Texture * texture)
{
    if (_isTiled)
    {
        texture->setRepeated(true);
        _textureRect.Dimension.x = _tiledArea.x;
        _textureRect.Dimension.y = _tiledArea.y;
    }
    else
    {
        if (_isWholeImage)
        {
            _textureRect.Dimension.x = texture->getSize().x;
            _textureRect.Dimension.y = texture->getSize().y;
        }
    }

    auto spriteRect = sf::Rect<int>(
        _textureRect.Position.x,
        _textureRect.Position.y,
        _textureRect.Dimension.x,
        _textureRect.Dimension.y);

    _sprite.reset(new sf::Sprite(*texture, spriteRect));
    _sprite->setOrigin(spriteRect.width / 2.0f, spriteRect.height / 2.0f);
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

void ImageDrawable::FetchDependencies(const Entity &entity)
{
    Drawable::FetchDependencies(entity);
    if (_textureKey != "")
    {
        SetupSprite(ResourceLibrary::Get<sf::Texture>(_textureKey));
    }
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
