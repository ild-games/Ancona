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

void priv::SpriteImpl::Draw(
    SDL_Renderer & sdlRenderer,
    const ild::View & view,
    const ildhal::RenderStates & renderStates)
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
    ild::Vector2f scaledSize = ild::Vector2f(
        renderStates.renderStatesImpl().size().x * std::abs(transform.scale().x),
        renderStates.renderStatesImpl().size().y * std::abs(transform.scale().y));

    ild::Vector2f viewPosition = view.center() - (view.size() / 2.0f);
    ild::Vector2f positionInView = transform.position() - viewPosition;

    SDL_FRect dest;
    dest.x = positionInView.x;
    dest.y = positionInView.y;
    dest.w = scaledSize.x;
    dest.h = scaledSize.y;

    SDL_FPoint sdlOrigin;
    sdlOrigin.x = _origin.x;
    sdlOrigin.y = _origin.y;

    int flip = SDL_FLIP_NONE;
    flip |= transform.scale().x < 0 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    flip |= transform.scale().y < 0 ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE;

    SDL_RenderCopyExF(
        &sdlRenderer,
        _sdlTexture,
        &src,
        &dest,
        (double) transform.rotation(),
        &sdlOrigin,
        (SDL_RendererFlip) flip);
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
    spriteImpl().Draw(
        renderTarget.renderTargetImpl().sdlRenderer(),
        renderTarget.renderTargetImpl().view(),
        renderStates);
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
