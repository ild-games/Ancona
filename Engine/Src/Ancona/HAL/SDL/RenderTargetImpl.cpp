#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>

#include <Ancona/Graphics/Rect.hpp>
#include <Ancona/HAL/SDL/DrawableImpl.hpp>
#include <Ancona/HAL/SDL/RenderStatesImpl.hpp>
#include <Ancona/HAL/SDL/RenderTargetImpl.hpp>
#include <Ancona/System/Log.hpp>
#include <Ancona/Util/Assert.hpp>

namespace ildhal
{

/* Pimpl Implementation */

priv::RenderTargetImpl::RenderTargetImpl(SDL_Renderer * renderer) :
        _sdlRenderer(std::unique_ptr<SDL_Renderer, SDL_RendererDestructor>(renderer))
{
    int imgFlags = IMG_INIT_PNG;
    ILD_Assert(IMG_Init(imgFlags) & imgFlags, "SDL_image failed to initialize!");

    ILD_Assert(TTF_Init() == 0, "SDL_ttf failed to initialize!");
}

/* HAL Interface Implementation */

void RenderTarget::Clear(const ild::Color & color)
{
    SDL_SetRenderDrawColor(&renderTargetImpl().sdlRenderer(), color.r, color.g, color.b, 255);
    SDL_RenderClear(&renderTargetImpl().sdlRenderer());
}

void RenderTarget::Draw(const Drawable & drawable, const RenderStates & states)
{
    // TODO, remove this function when all drawables have their own draw functions
}

ild::Vector2f RenderTarget::MapPixelToCoords(const ild::Vector2i & point, const ild::View & view) const
{
    ild::Vector2f viewPosition = view.center() - (view.size() / 2.0f);
    return ild::Vector2f(point.x, point.y) + viewPosition;
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
    renderTargetImpl().view(view);
}

} // namespace ildhal
