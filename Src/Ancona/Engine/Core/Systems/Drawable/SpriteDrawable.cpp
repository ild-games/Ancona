#include <Ancona/Engine/Core/Systems/Drawable/SpriteDrawable.hpp>
#include <Ancona/Engine/Resource/ResourceLibrary.hpp>

#include <iostream>

using namespace ild;

SpriteDrawable::SpriteDrawable(
        const PositionComponent & positionComponent, 
        const std::string textureKey,
        const RenderPriorityEnum priority,
        int priorityOffset,
        sf::Vector2f positionOffset,
        const std::string key) :
    Drawable(
            positionComponent,
            priority,
            priorityOffset,
            positionOffset,
            key)
{
    sf::Texture & texture = *ResourceLibrary::Get<sf::Texture>(textureKey);
    _sprite = new sf::Sprite(texture);
    _sprite->setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
    _rotation = 0.0f;
}

void SpriteDrawable::Draw(sf::RenderWindow & window)
{
    sf::Vector2f position = sf::Vector2f(
            _positionComponent.Position.x + _positionOffset.x,
            _positionComponent.Position.y + _positionOffset.y);
    _sprite->setPosition(position.x,position.y);
    _sprite->setRotation(_rotation);
    window.draw(*_sprite);
}

sf::Vector2u SpriteDrawable::GetSize()
{
    return _sprite->getTexture()->getSize();
}
