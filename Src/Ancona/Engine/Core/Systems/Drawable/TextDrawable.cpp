#include <Ancona/Engine/Core/Systems/Drawable/TextDrawable.hpp>
#include <Ancona/Engine/Core/Systems/Physics/BasePhysicsSystem.hpp>
#include <Ancona/Engine/Resource/ResourceLibrary.hpp>

REGISTER_POLYMORPHIC_SERIALIZER(ild::TextDrawable)

using namespace ild;

TextDrawable::TextDrawable(
        BasePhysicsSystem * physicsSystem,
        const std::string text,
        const std::string fontKey,
        const sf::Color color,
        const int characterSize,
        const int priority,
        int priorityOffset,
        sf::Vector2f positionOffset,
        bool smooth) :
    Drawable(
            physicsSystem,
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

void TextDrawable::Draw(sf::RenderWindow & window, float delta)
{
    auto pos = _physicsComponent->GetInfo().GetPosition();
    sf::Vector2f position = sf::Vector2f(
            pos.x + _positionOffset.x,
            pos.y + _positionOffset.y);
    _text->setPosition(position.x, position.y);
    window.draw(*_text);
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
void TextDrawable::SetText(std::string text) 
{ 
    _text->setString(text); 
    CenterOrigin();
}

sf::Vector2u TextDrawable::GetSize()
{
    return sf::Vector2u(_text->getLocalBounds().width, _text->getLocalBounds().height);
}

int TextDrawable::GetAlpha()
{
    return _text->getColor().a;
}

void TextDrawable::SetAlpha(int alpha)
{
    sf::Color * col = 
        new sf::Color(_text->getColor());
    col->a = alpha;
    _text->setColor(*col);
    delete col;
}
