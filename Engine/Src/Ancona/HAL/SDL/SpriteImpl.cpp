#include <Ancona/HAL/SDL/RenderStatesImpl.hpp>
#include <Ancona/HAL/SDL/RenderTargetImpl.hpp>
#include <Ancona/HAL/SDL/SpriteImpl.hpp>
#include <Ancona/HAL/SDL/TextureImpl.hpp>
#include <Ancona/System/Log.hpp>

namespace ildhal
{

/* Pimpl Implementation */

priv::SpriteImpl::SpriteImpl(SDL_Texture * sdlTexture, const ild::IntRect & rect) : _sdlTexture(sdlTexture), _rect(rect)
{
}

void priv::SpriteImpl::Draw(SDL_Renderer & sdlRenderer, const ildhal::RenderStates & renderStates)
{
    if (!_sdlTexture)
    {
        return;
    }

    SDL_Rect src;
    src.x = _rect.left;
    src.y = _rect.top;
    src.w = _rect.width;
    src.h = _rect.height;

    const ild::Transform & transform = renderStates.renderStatesImpl().transform();
    SDL_FRect dest;
    dest.x = transform.position().x - _origin.x;
    dest.y = transform.position().y - _origin.y;
    dest.w = renderStates.renderStatesImpl().size().x;
    dest.h = renderStates.renderStatesImpl().size().y;

    SDL_RenderCopyF(&sdlRenderer, _sdlTexture, &src, &dest);
}

/* HAL Interface Implementation */

Sprite::Sprite()
{
    _pimpl = std::make_unique<priv::SpriteImpl>();
}

Sprite::Sprite(const Texture & texture, const ild::IntRect & rectangle)
{
    _pimpl = std::make_unique<priv::SpriteImpl>(&texture.textureImpl().sdlTexture(), rectangle);
}

void Sprite::Draw(ildhal::RenderTarget & renderTarget, const ildhal::RenderStates & renderStates)
{
    spriteImpl().Draw(renderTarget.renderTargetImpl().sdlRenderer(), renderStates);
}

/* getters and setters */

void Sprite::origin(const ild::Vector2f & newOrigin)
{
    spriteImpl().origin(newOrigin);
}

void Sprite::origin(float x, float y)
{
    spriteImpl().origin(ild::Vector2f(x, y));
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
