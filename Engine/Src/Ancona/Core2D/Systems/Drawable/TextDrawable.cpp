#include <Ancona/Core2D/Systems/Drawable/TextDrawable.hpp>
#include <Ancona/Core2D/Systems/Physics/BasePhysicsSystem.hpp>
#include <Ancona/Framework/Resource/ResourceLibrary.hpp>

REGISTER_POLYMORPHIC_SERIALIZER(ild::TextDrawable)

using namespace ild;

TextDrawable::TextDrawable(
        const std::string text,
        const std::string fontKey,
        const sf::Color color,
        const int characterSize,
        const int priority,
        int priorityOffset,
        sf::Vector2f positionOffset,
        bool smooth) :
    Drawable(
            priority,
            priorityOffset,
            positionOffset)
{
     _text = std::unique_ptr<sf::Text>(new sf::Text(text, *ResourceLibrary::Get<sf::Font>(fontKey)));
     _text->setColor(color);
     _text->setCharacterSize(characterSize);
     if(!smooth)
     {
         const_cast<sf::Texture&>(_text->getFont()->getTexture(characterSize)).setSmooth(false);
     }
}

void TextDrawable::OnDraw(sf::RenderWindow &window, sf::Transform drawableTransform, float delta)
{
    sf::RenderStates states(drawableTransform);
    window.draw(*_text, states);
}


void TextDrawable::CenterOrigin()
{
    sf::FloatRect textRect = _text->getLocalBounds();
    _text->setOrigin(textRect.left + (textRect.width / 2.0f),
                     textRect.top  + (textRect.height / 2.0f));
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
    return sf::Vector2f(_text->getLocalBounds().width, _text->getLocalBounds().height);
}

int TextDrawable::alpha()
{
    return _text->getColor().a;
}

void TextDrawable::alpha(int alpha)
{
    sf::Color * col = 
        new sf::Color(_text->getColor());
    col->a = alpha;
    _text->setColor(*col);
    delete col;
}

