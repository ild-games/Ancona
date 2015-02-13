#include <Ancona/Engine/Core/Systems/Drawable/SpriteDrawable.hpp>
#include <Ancona/Engine/Resource/ResourceLibrary.hpp>

using namespace ild;

SpriteDrawable::SpriteDrawable(
        const BasePhysicsComponent & physicsComponent, 
        const std::string textureKey,
        const int priority,
        int priorityOffset,
        sf::Vector2f positionOffset) :
    Drawable(
            physicsComponent,
            priority,
            priorityOffset,
            positionOffset)
{
    sf::Texture & texture = *ResourceLibrary::Get<sf::Texture>(textureKey);
    _sprite = new sf::Sprite(texture);
    _sprite->setOrigin(
            texture.getSize().x / 2, 
            texture.getSize().y / 2);
    _rotation = 0.0f;
}

void SpriteDrawable::Draw(sf::RenderWindow & window, float delta)
{
    auto pos = _physicsComponent.GetInfo().GetPosition();
    sf::Vector2f position = sf::Vector2f(
            pos.x + _positionOffset.x,
            pos.y + _positionOffset.y);
    _sprite->setPosition(position.x,position.y);
    _sprite->setRotation(_rotation);
    window.draw(*_sprite);
}

sf::Vector2u SpriteDrawable::GetSize()
{
    return sf::Vector2u(
            _sprite->getLocalBounds().width,
            _sprite->getLocalBounds().height);
}

int SpriteDrawable::GetAlpha()
{
    return _sprite->getColor().a;
}

void SpriteDrawable::SetAlpha(int alpha)
{
    sf::Color * col = 
        new sf::Color(_sprite->getColor());
    col->a = alpha;
    _sprite->setColor(*col);
    delete col;
}
