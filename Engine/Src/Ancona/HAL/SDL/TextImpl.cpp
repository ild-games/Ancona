#include <Ancona/Framework/Resource/ResourceLibrary.hpp>
#include <Ancona/HAL/SDL/FontImpl.hpp>
#include <Ancona/HAL/SDL/TextImpl.hpp>

namespace ildhal
{

/* Pimpl Implementation */

/* HAL Interface Implementation */

Text::Text() : _fontKey(std::string())
{
    _pimpl = std::make_unique<priv::TextImpl>();
}

Text::Text(const std::string & string, const std::string & fontKey, unsigned int characterSize) : _fontKey(fontKey)
{
    _pimpl = std::make_unique<priv::TextImpl>();
}

/* getters and setters */

void Text::origin(const ild::Vector2f & origin)
{
}

void Text::origin(float x, float y)
{
}

const ild::Color Text::fillColor() const
{
    return ild::Color::Black;
}

void Text::fillColor(const ild::Color & color)
{
}

ild::FloatRect Text::localBounds() const
{
    return ild::FloatRect(0.0f, 0.0f, 0.0f, 0.0f);
}

unsigned int Text::characterSize() const
{
    return 0;
}

void Text::characterSize(unsigned int size)
{
}

const std::string & Text::string() const
{
    return textImpl().text();
}

void Text::string(const std::string & newString)
{
}

const std::string & Text::fontKey() const
{
    return _fontKey;
}

void Text::fontKey(const std::string & fontKey)
{
    _fontKey = fontKey;
}

bool Text::smooth() const
{
    return false;
}

void Text::smooth(bool newSmooth) const
{
}

priv::TextImpl & Text::textImpl() const
{
    return static_cast<priv::TextImpl &>(*_pimpl);
}

} // namespace ildhal
