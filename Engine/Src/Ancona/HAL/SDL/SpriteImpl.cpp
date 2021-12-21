#include <Ancona/HAL/SDL/SpriteImpl.hpp>
#include <Ancona/HAL/SDL/TextureImpl.hpp>

namespace ildhal
{

/* Pimpl Implementation */

/* HAL Interface Implementation */

Sprite::Sprite()
{
    _pimpl = std::make_unique<priv::SpriteImpl>();
}

Sprite::Sprite(const Texture & texture, const ild::IntRect & rectangle)
{
    _pimpl = std::make_unique<priv::SpriteImpl>();
}

/* getters and setters */

void Sprite::origin(const ild::Vector2f & newOrigin)
{
}

void Sprite::origin(float x, float y)
{
}

const ild::Color Sprite::color() const
{
    return ild::Color::Black;
}

void Sprite::color(const ild::Color & newColor)
{
}

void Sprite::texture(const Texture & newTexture, bool resetRect)
{
}

priv::SpriteImpl & Sprite::spriteImpl() const
{
    return static_cast<priv::SpriteImpl &>(*_pimpl);
}

} // namespace ildhal
