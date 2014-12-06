#include <Ancona/Engine/Core/Systems/SpriteComponent.hpp>
#include <Ancona/Engine/Resource/ResourceLibrary.hpp>


using namespace ild;

SpriteComponent::SpriteComponent(
        PositionComponent & positionComponent, 
        const std::string textureKey,
        const RenderPriorityEnum priority,
        int priorityOffset)
    : _positionComponent(positionComponent),
      _renderPriority(priority),
      _priorityOffset(priorityOffset)
{
    auto * texture = ResourceLibrary::Get<sf::Texture>(textureKey);
    _sprite.setTexture(*texture);
    _sprite.setOrigin(texture->getSize().x / 2, texture->getSize().y / 2);
    _rotation = 0.0f;
}

void SpriteComponent::Draw(sf::RenderWindow & window)
{
    auto & position = _positionComponent.Position;
    _sprite.setPosition(position.x,position.y);
    _sprite.setRotation(_rotation);
    window.draw(_sprite);
}



/* getters and setters */
void SpriteComponent::SetRotation(float rotation)
{
    _rotation = rotation;
}
void SpriteComponent::SetOrigin(float x, float y)
{
    _sprite.setOrigin(x, y);
}
void SpriteComponent::SetOrigin(sf::Vector2f newOrigin)
{
    _sprite.setOrigin(newOrigin);
}
float SpriteComponent::GetRotation()
{
    return _rotation;
}
sf::Sprite * SpriteComponent::GetSprite()
{
    return &_sprite;
}
RenderPriorityEnum SpriteComponent::GetRenderPriority()
{
    return _renderPriority;
}
int SpriteComponent::GetPriorityOffset()
{
    return _priorityOffset;
}
