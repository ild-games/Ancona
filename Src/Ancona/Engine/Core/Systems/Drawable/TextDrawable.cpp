#include <Ancona/Engine/Core/Systems/Drawable/TextDrawable.hpp>
#include <Ancona/Engine/Core/Systems/Physics/PlatformPhysicsSystem.hpp>
#include <Ancona/Engine/Resource/ResourceLibrary.hpp>

using namespace ild;

TextDrawable::TextDrawable(
        const BasePhysicsComponent & physicsComponent,
        const std::string text,
        const std::string fontKey,
        const sf::Color color,
        const int characterSize,
        const int priority,
        int priorityOffset,
        sf::Vector2f positionOffset,
        bool smooth) :
    Drawable(
            physicsComponent,
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
    auto pos = _physicsComponent.GetInfo().GetPosition();
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

void * TextDrawable::Inflate(
        const Json::Value & object,
        const Entity & entity,
        LoadingContext * loadingContext)
{
    TextDrawable * text = new TextDrawable(
            *loadingContext->GetSystems().GetSystem<BasePhysicsSystem>("physics")->at(entity),
            object["text"].asString(),
            object["font-key"].asString(),
            sf::Color(
                object["color"]["red"].asUInt64(), 
                object["color"]["green"].asUInt64(), 
                object["color"]["blue"].asUInt64(), 
                object["color"]["alpha"].asUInt64()),
            object["character-size"].asInt(),
            object["render-priority"].asInt(),
            object["priority-offset"].asInt(),
            sf::Vector2f(object["position-offset"]["x"].asFloat(), object["position-offset"]["y"].asFloat()),
            object["smooth"].asBool());
    return text;
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
