#include <Ancona/Engine/Core/Systems/SpriteComponent.hpp>
#include <Ancona/Engine/Resource/ResourceLibrary.hpp>

using namespace ild;

SpriteComponent::SpriteComponent(
        PositionComponent & positionComponent, 
        const std::string textureKey)
    : _positionComponent(positionComponent)
{
    auto * texture = ResourceLibrary::Get<sf::Texture>(textureKey);
    _sprite.setTexture(*texture);
}

void SpriteComponent::Draw(sf::RenderWindow & window)
{
    auto & position = _positionComponent.Position;
    _sprite.setPosition(position.x,position.y);
    window.draw(_sprite);
}
