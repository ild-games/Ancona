#include <Ancona/Core2D/Systems/Drawable/SoloImage.hpp>

REGISTER_POLYMORPHIC_SERIALIZER(ild::SoloImage)

using namespace ild;

void SoloImage::Draw(sf::RenderWindow & window, float delta)
{
    _sprite->setPosition(_position.x, _position.y);
    _sprite->setRotation(_rotation);
    window.draw(*_sprite);
}

void SoloImage::SetupSprite()
{
    sf::Texture & texture = *ResourceLibrary::Get<sf::Texture>(_textureKey);
    _sprite.reset(new sf::Sprite(texture));
    _sprite->setOrigin(
            texture.getSize().x / 2,
            texture.getSize().y / 2);
}

void SoloImage::Serialize(Archive & arc)
{
    Image::Serialize(arc);
}

/* getters and setters */
sf::Vector2u SoloImage::size()
{
    return sf::Vector2u(
            _sprite->getLocalBounds().width,
            _sprite->getLocalBounds().height);
}
