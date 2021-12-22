#pragma once

#include <SDL2/SDL.h>

#include <Ancona/HAL/RenderStates.hpp>
#include <Ancona/HAL/SDL/DrawableImpl.hpp>
#include <Ancona/HAL/Sprite.hpp>
#include <Ancona/Util/Vector2.hpp>

namespace ildhal
{

namespace priv
{

class SpriteImpl : public DrawableImpl
{
  public:
    SpriteImpl() {}
    SpriteImpl(SDL_Texture * sdlTexture);

    void Draw(SDL_Renderer & sdlRenderer, const ildhal::RenderStates & renderStates, const ild::Vector2f & size);

  private:
    SDL_Texture * _sdlTexture = nullptr;
};

} // namespace priv

} // namespace ildhal
