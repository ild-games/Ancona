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
            anchor)
{
     _text = std::unique_ptr<sf::Text>(new sf::Text(text, *ResourceLibrary::Get<sf::Font>(fontKey)));
     _text->setFillColor(color);
     _text->setCharacterSize(characterSize);
     if(!smooth)
     {
         const_cast<sf::Texture&>(_text->getFont()->getTexture(characterSize)).setSmooth(false);
     }
}

Drawable * TextDrawable::Copy() {
    Assert(false, "TextDrawable copy not implemented.");
    auto drawable = new TextDrawable();
    Drawable::CopyProperties(drawable);
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
    _text->setOrigin(textRect.left + (textRect.width * _anchor.x),
                     textRect.top  + (textRect.height * _anchor.y));
}

void TextDrawable::Serialize(Archive &archive) {
    Drawable::Serialize(archive);
    archive(_text, "text");
}

void TextDrawable::FetchDependencies(const Entity &entity) {
    Drawable::FetchDependencies(entity);
    CenterOrigin();
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

