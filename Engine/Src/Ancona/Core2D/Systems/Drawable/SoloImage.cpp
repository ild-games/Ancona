#include <Ancona/Core2D/Systems/Drawable/SoloImage.hpp>

REGISTER_POLYMORPHIC_SERIALIZER(ild::SoloImage)

using namespace ild;

SoloImage::SoloImage(std::string textureKey): Image(textureKey) { }

void SoloImage::Draw(sf::RenderWindow & window, float delta)
{
    _sprite->setPosition(_position.x, _position.y);
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

void SoloImage::rotation(float newRotation)
{
    _sprite->setRotation(newRotation);
}

void SoloImage::scale(sf::Vector2f newScale)
{
    _sprite->setScale(newScale);
}
