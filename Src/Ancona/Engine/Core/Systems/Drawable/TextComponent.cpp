#include <Ancona/Engine/Core/Systems/Drawable/TextComponent.hpp>
#include <Ancona/Engine/Resource/ResourceLibrary.hpp>

using namespace ild;

TextComponent::TextComponent(
        const PositionComponent & positionComponent,
        const std::string text,
        const std::string fontKey,
        const sf::Color color,
        const int characterSize,
        const RenderPriorityEnum priority,
        int priorityOffset,
        bool smooth) :
    DrawableComponent(
            positionComponent,
            priority,
            priorityOffset)
{
    _text = new sf::Text(text, *ResourceLibrary::Get<sf::Font>(fontKey));
    _text->setColor(color);
    _text->setCharacterSize(characterSize);
    if(!smooth)
    {
        const_cast<sf::Texture&>(_text->getFont()->getTexture(characterSize)).setSmooth(false);
    }
    CenterOrigin();
}

void TextComponent::Draw(sf::RenderWindow & window)
{
    auto & position = _positionComponent.Position;
    _text->setPosition(position.x, position.y);
    window.draw(*_text);
}


void TextComponent::CenterOrigin()
{
    sf::FloatRect textRect = _text->getLocalBounds();
    _text->setOrigin(textRect.left + (textRect.width / 2.0f),
                     textRect.top  + (textRect.height / 2.0f));
}

/* getters and setters */
void TextComponent::SetText(std::string text) 
{ 
    _text->setString(text); 
    CenterOrigin();
}

sf::Vector2u TextComponent::GetSize()
{
    return sf::Vector2u(_text->getLocalBounds().width, _text->getLocalBounds().height);
}
