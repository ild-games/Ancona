#include <Ancona/Core2D/Systems/Drawable/ImageDrawable.hpp>
#include <Ancona/Util2D/VectorMath.hpp>

REGISTER_POLYMORPHIC_SERIALIZER(ild::ImageDrawable);

using namespace ild;

ImageDrawable::ImageDrawable(
        std::string textureKey,
        const int priority,
        const std::string & key) :
    Drawable(priority, key),
    _textureKey(textureKey)
{
}

ImageDrawable::ImageDrawable(
        const int priority,
        const std::string & key) :
    Drawable(priority, key),
    _textureKey("")
{
}

Drawable * ImageDrawable::Copy() {
    auto drawable = new ImageDrawable();
    Drawable::CopyProperties(drawable);
    drawable->textureKey(_textureKey);
    drawable->textureRect(_textureRect);
    drawable->tiledArea(_tiledArea);
    drawable->isTiled(_isTiled);
    drawable->isWholeImage(_isWholeImage);
    drawable->SetupSprite();
    return drawable;
}

void ImageDrawable::OnDraw(sf::RenderWindow &window, sf::Transform drawableTransform, float delta)
{
    if (_sprite.get() != NULL)
    {
        sf::RenderStates states(drawableTransform);
        window.draw(*_sprite, states);
    }
}

void ImageDrawable::SetupSprite()
{
    if (_textureKey == "") 
    {
        return;
    }

    SetupSprite(ResourceLibrary::Get<sf::Texture>(_textureKey));
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
    _sprite->setOrigin(spriteRect.width * _anchor.x, spriteRect.height * _anchor.y);
    _sprite->setColor(_color);
    sf::Color col(_sprite->getColor());
    col.a = _alpha;
    _sprite->setColor(col);
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
    if (_isTiled) 
    {
        return VectorMath::ComponentMultiplication(_tiledArea, _scale);
    }
    else 
    {
        return VectorMath::ComponentMultiplication(_textureRect.Dimension, _scale);
    }
}
