#pragma once

#include <memory>

#include "SDL2/SDL.h"

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

    SDL_Renderer & sdlRenderer() const { return *_sdlRenderer; };

  private:
    std::unique_ptr<SDL_Renderer, SDL_RendererDestructor> _sdlRenderer;
};

} // namespace priv

} // namespace ildhal
