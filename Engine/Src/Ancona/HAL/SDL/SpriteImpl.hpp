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
    SpriteImpl(SDL_Texture * sdlTexture, const ild::IntRect & rect);

    void Draw(SDL_Renderer & sdlRenderer, const ildhal::RenderStates & renderStates);

    /* getters and setters */
    void origin(const ild::Vector2f & newOrigin) { _origin = newOrigin; }

  private:
    SDL_Texture * _sdlTexture = nullptr;
    ild::Vector2f _origin = ild::Vector2f(0.0f, 0.0f);
    ild::IntRect _rect;
};

} // namespace priv

} // namespace ildhal
