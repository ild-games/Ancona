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
    drawable->SetupSprite();
    return drawable;
}

void ImageDrawable::OnDraw(ildhal::RenderTarget & target, Transform drawableTransform, float delta)
{
    if (_sprite.get() != NULL)
    {
        ildhal::RenderStates states(drawableTransform);
        target.Draw(*_sprite, states);
    }
}

void ImageDrawable::SetupSprite()
{
    if (_textureKey == "")
    {
        return;
    }

    SetupSprite(ResourceLibrary::Get<ildhal::Texture>(_textureKey));
}

void ImageDrawable::SetupSprite(ildhal::Texture * texture)
{
    if (_isTiled)
    {
        texture->smooth(false);
        texture->repeated(true);
        _textureRect.Dimension.x = _tiledArea.x;
        _textureRect.Dimension.y = _tiledArea.y;
    }
    else
    {
        texture->smooth(true);
        if (_isWholeImage)
        {
            _textureRect.Dimension.x = texture->size().x;
            _textureRect.Dimension.y = texture->size().y;
        }
    }

    auto spriteRect = ild::Rect<int>(
        _textureRect.Position.x,
        _textureRect.Position.y,
        _textureRect.Dimension.x,
        _textureRect.Dimension.y);

    _sprite.reset(new ildhal::Sprite(*texture, spriteRect));
    _sprite->origin(spriteRect.width * _anchor.x, spriteRect.height * _anchor.y);
    ApplyColor();
    ApplyAlpha();
}

void ImageDrawable::ApplyAlpha()
{
    Color col(_sprite->color());
    col.a = _alpha;
    _sprite->color(col);
}

void ImageDrawable::ApplyColor()
{
    _sprite->color(_color);
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
        SetupSprite(ResourceLibrary::Get<ildhal::Texture>(_textureKey));
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
    _alpha = newAlpha;
    ApplyAlpha();
}

void ImageDrawable::color(Color newColor)
{
    _color = newColor;
    ApplyColor();
}

} // namespace ild
