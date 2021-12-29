#include <Ancona/Core2D/Systems/Drawable/TextDrawable.hpp>
#include <Ancona/Core2D/Systems/PositionSystem.hpp>
#include <Ancona/Framework/Resource/ResourceLibrary.hpp>
#include <Ancona/Graphics/Rect.hpp>
#include <Ancona/HAL.hpp>
#include <Ancona/System/Log.hpp>
#include <Ancona/Util2D/VectorMath.hpp>

REGISTER_POLYMORPHIC_SERIALIZER(ild::TextDrawable)

namespace ild
{

TextDrawable::TextDrawable(
    const std::string & text,
    const std::string & fontKey,
    const Color color,
    const int characterSize,
    const float priority,
    const std::string & key,
    float priorityOffset,
    Vector2f anchor,
    bool smooth) :
        Drawable(priority, key, priorityOffset, anchor),
        _fontKey(fontKey),
        _color(color),
        _characterSize(characterSize),
        _smooth(smooth),
        _text(std::make_unique<ildhal::Text>(text, fontKey))
{
    SetupText();
}

TextDrawable::TextDrawable(const std::string & text, const std::string & fontKey) : Drawable()
{
    _text = std::make_unique<ildhal::Text>(text, fontKey);
}

Drawable * TextDrawable::Copy()
{
    auto drawable = new TextDrawable(_text->string(), _text->fontKey());
    Drawable::CopyProperties(drawable);
    drawable->_color = _color;
    drawable->_characterSize = _characterSize;
    drawable->_smooth = _smooth;
    drawable->SetupText();
    return drawable;
}

void TextDrawable::OnDraw(ildhal::RenderTarget & target, Transform drawableTransform, float delta)
{
    ildhal::RenderStates states(drawableTransform);
    _text->Draw(target, states);
}

void TextDrawable::Serialize(Archive & archive)
{
    Drawable::Serialize(archive);
    archive(_text, "text");
    _color = _text->fillColor();
    _characterSize = _text->characterSize();
    _smooth = _text->smooth();
}

void TextDrawable::FetchDependencies(const Entity & entity)
{
    Drawable::FetchDependencies(entity);
}

void TextDrawable::SetupText()
{
    _text->fillColor(_color);
    _text->characterSize(_characterSize);
    if (!_smooth)
    {
        _text->smooth(false);
    }
}

/* getters and setters */
void TextDrawable::text(const std::string & text)
{
    _text->string(text);
}

Vector2f TextDrawable::size()
{
    Vector2f size(_text->localBounds().width, _text->localBounds().height);
    return size;
}

int TextDrawable::alpha()
{
    return _text->fillColor().a;
}

void TextDrawable::alpha(int alpha)
{
    Color col(_text->fillColor());
    col.a = alpha;
    _text->fillColor(col);
}

} // namespace ild
