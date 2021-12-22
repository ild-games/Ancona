#include <SDL2_image/SDL_image.h>

#include <Ancona/Graphics/Rect.hpp>
#include <Ancona/HAL/SDL/DrawableImpl.hpp>
#include <Ancona/HAL/SDL/RenderStatesImpl.hpp>
#include <Ancona/HAL/SDL/RenderTargetImpl.hpp>
#include <Ancona/HAL/SDL/ViewImpl.hpp>
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
}

/* HAL Interface Implementation */

void RenderTarget::Clear(const ild::Color & color)
{
    SDL_SetRenderDrawColor(&renderTargetImpl().sdlRenderer(), color.r, color.g, color.b, color.a);
    SDL_RenderClear(&renderTargetImpl().sdlRenderer());
}

void RenderTarget::Draw(const Drawable & drawable, const RenderStates & states)
{
    // TODO, remove this function when all drawables have their own draw functions
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
    const ild::Vector2f & size = view.size();
    const ild::Vector2f & center = view.center();

    SDL_Rect rect;
    rect.x = (int) (center.x - (size.x / 2.0f));
    rect.y = (int) (center.y - (size.y / 2.0f));
    rect.w = (int) size.x;
    rect.h = (int) size.y;
}

} // namespace ildhal
