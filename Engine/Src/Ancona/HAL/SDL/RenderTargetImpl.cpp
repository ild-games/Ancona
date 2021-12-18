#include <Ancona/HAL/SDL/DrawableImpl.hpp>
#include <Ancona/HAL/SDL/RenderStatesImpl.hpp>
#include <Ancona/HAL/SDL/RenderTargetImpl.hpp>
#include <Ancona/HAL/SDL/ViewImpl.hpp>

namespace ildhal
{

/* Pimpl Implementation */

priv::RenderTargetImpl::RenderTargetImpl(SDL_Renderer * renderer) :
        _sdlRenderer(std::unique_ptr<SDL_Renderer, SDL_RendererDestructor>(renderer))
{
}

/* HAL Interface Implementation */

void RenderTarget::Clear(const ild::Color & color)
{
    SDL_SetRenderDrawColor(&renderTargetImpl().sdlRenderer(), color.r, color.g, color.b, color.a);
    SDL_RenderClear(&renderTargetImpl().sdlRenderer());
}

void RenderTarget::Draw(const Drawable & drawable, const RenderStates & states)
{
}

ild::Vector2f RenderTarget::MapPixelToCoords(const ild::Vector2i & point, const ild::View & view) const
{
    return ild::Vector2f(0.0f, 0.0f);
}

void RenderTarget::ResetGLStates()
{
}

/* getters and setters */
const ild::View RenderTarget::defaultView() const
{
    ild::View view;
    return view;
}

void RenderTarget::view(const ild::View & view)
{
}

} // namespace ildhal
