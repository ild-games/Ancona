#include <Ancona/Engine/Core/Systems/Drawable/SpriteComponent.hpp>
#include <Ancona/Engine/Resource/ResourceLibrary.hpp>


using namespace ild;

SpriteComponent::SpriteComponent(
        const PositionComponent & positionComponent, 
        const std::string textureKey,
        const RenderPriority::RenderPriority priority,
        int priorityOffset) : 
    DrawableComponent(
            positionComponent,
            priority,
            priorityOffset)
{
    sf::Texture & texture = *ResourceLibrary::Get<sf::Texture>(textureKey);
    _sprite = new sf::Sprite(texture);
    _sprite->setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
    _rotation = 0.0f;
}

void SpriteComponent::Draw(sf::RenderWindow & window)
{
    auto & position = _positionComponent.Position;
    _sprite->setPosition(position.x,position.y);
    _sprite->setRotation(_rotation);
    window.draw(*_sprite);
}

sf::Vector2u SpriteComponent::GetSize()
{
    return _sprite->getTexture()->getSize();
}
