#include <Ancona/Engine/Core/Systems/Drawable/TextDrawable.hpp>
#include <Ancona/Engine/Resource/ResourceLibrary.hpp>

#include <iostream>

using namespace ild;

TextDrawable::TextDrawable(
        const PositionComponent & positionComponent,
        const std::string text,
        const std::string fontKey,
        const sf::Color color,
        const int characterSize,
        const RenderPriorityEnum priority,
        int priorityOffset,
        sf::Vector2f positionOffset,
        bool smooth) :
    Drawable(
            positionComponent,
            priority,
            priorityOffset,
            positionOffset)
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

void TextDrawable::Draw(sf::RenderWindow & window, float delta)
{
    sf::Vector2f position = sf::Vector2f(
            _positionComponent.Position.x + _positionOffset.x,
            _positionComponent.Position.y + _positionOffset.y);
    _text->setPosition(position.x, position.y);
    window.draw(*_text);
}


void TextDrawable::CenterOrigin()
{
    sf::FloatRect textRect = _text->getLocalBounds();
    _text->setOrigin(textRect.left + (textRect.width / 2.0f),
                     textRect.top  + (textRect.height / 2.0f));
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
