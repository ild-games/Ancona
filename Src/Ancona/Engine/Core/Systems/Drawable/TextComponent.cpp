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
    _textStr = text;
    _text->setColor(color);
    _text->setCharacterSize(characterSize);
    if(!smooth)
    {
        const_cast<sf::Texture&>(_text->getFont()->getTexture(characterSize)).setSmooth(false);
    }
}

void TextComponent::Draw(sf::RenderWindow & window)
{
    _text->setString(_textStr);
    auto & position = _positionComponent.Position;
    _text->setPosition(position.x,position.y);
    window.draw(*_text);
}

sf::Vector2u TextComponent::GetSize()
{
    return _text->getFont()->getTexture(_text->getCharacterSize()).getSize();
}
