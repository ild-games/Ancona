#include <Ancona/HAL/SFML/SpriteImpl.hpp>
#include <Ancona/HAL/SFML/TextureImpl.hpp>

namespace ildhal
{

/* Pimpl Implementation */

priv::SpriteImpl::SpriteImpl()
{
    _sfmlDrawable = std::make_unique<sf::Sprite>();
}

priv::SpriteImpl::SpriteImpl(const sf::Texture &texture, const sf::IntRect &rectangle)
{
    _sfmlDrawable = std::make_unique<sf::Sprite>(texture, rectangle);
}

sf::Sprite &priv::SpriteImpl::sfmlSprite() const
{
    return static_cast<sf::Sprite &>(*_sfmlDrawable);
}

/* HAL Interface Implementation */

Sprite::Sprite()
{
    _pimpl = std::make_unique<priv::SpriteImpl>();
}

Sprite::Sprite(const Texture &texture, const ild::IntRect &rectangle)
{
    _pimpl = std::make_unique<priv::SpriteImpl>(
        texture.textureImpl().sfmlTexture(),
        sf::IntRect(rectangle.left, rectangle.top, rectangle.width, rectangle.height));
}

/* getters and setters */

void Sprite::origin(const ild::Vector2f &newOrigin)
{
    spriteImpl().sfmlSprite().setOrigin(sf::Vector2f(newOrigin.x, newOrigin.y));
}

void Sprite::origin(float x, float y)
{
    spriteImpl().sfmlSprite().setOrigin(x, y);
}

const ild::Color &Sprite::color() const
{
    ild::Color color(spriteImpl().sfmlSprite().getColor().toInteger());
    return color;
}

void Sprite::color(const ild::Color &newColor)
{
    spriteImpl().sfmlSprite().setColor(sf::Color(newColor.toInteger()));
}

void Sprite::texture(const Texture &newTexture, bool resetRect)
{
    spriteImpl().sfmlSprite().setTexture(newTexture.textureImpl().sfmlTexture(), resetRect);
}

priv::SpriteImpl &Sprite::spriteImpl() const
{
    return static_cast<priv::SpriteImpl &>(*_pimpl);
}

} // namespace ildhal
