#include <Ancona/Core2D/Systems/Drawable/TextDrawable.hpp>
#include <Ancona/Core2D/Systems/Position/PositionSystem.hpp>
#include <Ancona/Framework/Resource/ResourceLibrary.hpp>
#include <Ancona/Util2D/VectorMath.hpp>

REGISTER_POLYMORPHIC_SERIALIZER(ild::TextDrawable)

using namespace ild;

TextDrawable::TextDrawable(
        const std::string text,
        const std::string fontKey,
        const sf::Color color,
        const int characterSize,
        const int priority,
        const std::string & key,
        int priorityOffset,
        sf::Vector2f anchor,
        bool smooth) :
    Drawable(
            priority,
            key,
            priorityOffset,
            anchor),
    _fontKey(fontKey),
    _color(color),
    _characterSize(characterSize),
    _smooth(smooth) {
    _text = std::unique_ptr<sf::Text>(new sf::Text(text, *ResourceLibrary::Get<sf::Font>(fontKey)));
    SetupText();
}

TextDrawable::TextDrawable(const std::string & text, const sf::Font * font) : Drawable() {
    _text = std::unique_ptr<sf::Text>(new sf::Text(text, *font));
}

Drawable * TextDrawable::Copy() {
    auto drawable = new TextDrawable(_text->getString(), _text->getFont());
    Drawable::CopyProperties(drawable);
    drawable->_color = _color;
    drawable->_characterSize = _characterSize;
    drawable->_smooth = _smooth;
    drawable->SetupText();
    return drawable;
}

void TextDrawable::OnDraw(sf::RenderWindow &window, sf::Transform drawableTransform, float delta)
{
    sf::RenderStates states(drawableTransform);
    window.draw(*_text, states);
}


void TextDrawable::CenterOrigin()
{
    sf::FloatRect textRect = _text->getLocalBounds();
    _text->setOrigin(
        textRect.left + (textRect.width * _anchor.x),
        textRect.top  + (textRect.height * _anchor.y));
}

void TextDrawable::Serialize(Archive &archive) {
    Drawable::Serialize(archive);
    archive(_text, "text");
    _color = _text->getFillColor();
    _characterSize = _text->getCharacterSize();
    _smooth = const_cast<sf::Texture&>(_text->getFont()->getTexture(_characterSize)).isSmooth();
}

void TextDrawable::FetchDependencies(const Entity &entity) {
    Drawable::FetchDependencies(entity);
    CenterOrigin();
}

void TextDrawable::SetupText() {
    _text->setFillColor(_color);
    _text->setCharacterSize(_characterSize);
    if (!_smooth) {
        const_cast<sf::Texture&>(_text->getFont()->getTexture(_characterSize)).setSmooth(false);
    }
}

/* getters and setters */
void TextDrawable::text(std::string text)
{ 
    _text->setString(text); 
    CenterOrigin();
}

sf::Vector2f TextDrawable::size()
{
    sf::Vector2f size(_text->getLocalBounds().width, _text->getLocalBounds().height);
    return VectorMath::ComponentMultiplication(size, _scale);
}

int TextDrawable::alpha()
{
    return _text->getFillColor().a;
}

void TextDrawable::alpha(int alpha)
{
    sf::Color * col = 
        new sf::Color(_text->getFillColor());
    col->a = alpha;
    _text->setFillColor(*col);
    delete col;
}

