#include <Ancona/Framework/Resource/ResourceLibrary.hpp>
#include <Ancona/HAL/SFML/FontImpl.hpp>
#include <Ancona/HAL/SFML/TextImpl.hpp>

namespace ildhal
{

/* Pimpl Implementation */

priv::TextImpl::TextImpl()
{
    _sfmlDrawable = std::make_unique<sf::Text>();
}

priv::TextImpl::TextImpl(const std::string & string, const sf::Font & font, unsigned int characterSize) :
        _underlyingSfmlString(string)
{
    _sfmlDrawable = std::make_unique<sf::Text>(string, font, characterSize);
}

sf::Text & priv::TextImpl::sfmlText() const
{
    return static_cast<sf::Text &>(*_sfmlDrawable);
}

void priv::TextImpl::underlyingSfmlString(const std::string & string)
{
    _underlyingSfmlString = string;
}

const std::string & priv::TextImpl::underlyingSfmlString() const
{
    return _underlyingSfmlString;
}

/* HAL Interface Implementation */

Text::Text() : _fontKey(std::string())
{
    _pimpl = std::make_unique<priv::TextImpl>();
}

Text::Text(const std::string & string, const std::string & fontKey, unsigned int characterSize) : _fontKey(fontKey)
{
    _pimpl = std::make_unique<priv::TextImpl>(
        string,
        ild::ResourceLibrary::Get<Font>(fontKey)->fontImpl().sfmlFont(),
        characterSize);
}

/* getters and setters */

void Text::origin(const ild::Vector2f & origin)
{
    textImpl().sfmlText().setOrigin(sf::Vector2f(origin.x, origin.x));
}

void Text::origin(float x, float y)
{
    textImpl().sfmlText().setOrigin(x, y);
}

const ild::Color Text::fillColor() const
{
    return ild::Color(textImpl().sfmlText().getFillColor().toInteger());
}

void Text::fillColor(const ild::Color & color)
{
    textImpl().sfmlText().setFillColor(sf::Color(color.toInteger()));
}

ild::FloatRect Text::localBounds() const
{
    auto sfmlBounds = textImpl().sfmlText().getLocalBounds();

    ild::FloatRect bounds(sfmlBounds.left, sfmlBounds.top, sfmlBounds.width, sfmlBounds.height);

    return bounds;
}

unsigned int Text::characterSize() const
{
    return textImpl().sfmlText().getCharacterSize();
}

void Text::characterSize(unsigned int size)
{
    textImpl().sfmlText().setCharacterSize(size);
}

const std::string & Text::string() const
{
    return textImpl().underlyingSfmlString();
}

void Text::string(const std::string & newString)
{
    textImpl().underlyingSfmlString(newString);
    textImpl().sfmlText().setString(newString);
}

const std::string & Text::fontKey() const
{
    return _fontKey;
}

void Text::fontKey(const std::string & fontKey)
{
    Font * font = ild::ResourceLibrary::Get<Font>(fontKey);
    _fontKey = fontKey;
    priv::FontImpl & fontImpl = font->fontImpl();
    sf::Font & sfmlFont = fontImpl.sfmlFont();

    textImpl().sfmlText().setFont(sfmlFont);
}

bool Text::smooth() const
{
    auto characterSize = textImpl().sfmlText().getCharacterSize();
    return const_cast<sf::Texture &>(textImpl().sfmlText().getFont()->getTexture(characterSize)).isSmooth();
}

void Text::smooth(bool newSmooth) const
{
    auto characterSize = textImpl().sfmlText().getCharacterSize();
    const_cast<sf::Texture &>(textImpl().sfmlText().getFont()->getTexture(characterSize)).setSmooth(newSmooth);
}

priv::TextImpl & Text::textImpl() const
{
    return static_cast<priv::TextImpl &>(*_pimpl);
}

} // namespace ildhal
