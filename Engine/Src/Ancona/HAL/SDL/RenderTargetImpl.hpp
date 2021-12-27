#pragma once

#include <memory>

#include "SDL2/SDL.h"

#include <Ancona/Graphics/View.hpp>
#include <Ancona/HAL/RenderTarget.hpp>

namespace ildhal
{

namespace priv
{

struct SDL_RendererDestructor
{
    void operator()(SDL_Renderer * r) const { SDL_DestroyRenderer(r); }
};

class RenderTargetImpl
{
  public:
    RenderTargetImpl() {}
    RenderTargetImpl(SDL_Renderer *);

    /* getters and setters */
    const ild::View & view() const { return _view; };
    void view(const ild::View & view) { _view = view; };
    SDL_Renderer & sdlRenderer() const { return *_sdlRenderer; };

  private:
    ild::View _view;

    std::unique_ptr<SDL_Renderer, SDL_RendererDestructor> _sdlRenderer;
};

} // namespace priv

} // namespace ildhal
