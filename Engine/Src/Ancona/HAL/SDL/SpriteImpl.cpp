#include <Ancona/HAL/SDL/RenderStatesImpl.hpp>
#include <Ancona/HAL/SDL/RenderTargetImpl.hpp>
#include <Ancona/HAL/SDL/SpriteImpl.hpp>
#include <Ancona/HAL/SDL/TextureImpl.hpp>

namespace ildhal
{

/* Pimpl Implementation */

priv::SpriteImpl::SpriteImpl(SDL_Texture * sdlTexture) : _sdlTexture(sdlTexture)
{
}

void priv::SpriteImpl::Draw(
    SDL_Renderer & sdlRenderer,
    const ildhal::RenderStates & renderStates,
    const ild::Vector2f & size)
{
    if (!_sdlTexture)
    {
        return;
    }

    const ild::Transform & transform = renderStates.renderStatesImpl().transform();
    SDL_FRect dest;
    dest.x = transform.position().x;
    dest.y = transform.position().y;
    dest.w = size.x;
    dest.h = size.y;

    SDL_RenderCopyF(&sdlRenderer, _sdlTexture, nullptr, &dest);
}

/* HAL Interface Implementation */

Sprite::Sprite()
{
    _pimpl = std::make_unique<priv::SpriteImpl>();
}

Sprite::Sprite(const Texture & texture, const ild::IntRect & rectangle)
{
    _pimpl = std::make_unique<priv::SpriteImpl>(&texture.textureImpl().sdlTexture());
}

void Sprite::Draw(
    ildhal::RenderTarget & renderTarget,
    const ildhal::RenderStates & renderStates,
    const ild::Vector2f & size)
{
    spriteImpl().Draw(renderTarget.renderTargetImpl().sdlRenderer(), renderStates, size);
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
