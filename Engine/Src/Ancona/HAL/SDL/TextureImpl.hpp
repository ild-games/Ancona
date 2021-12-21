#pragma once

#include <memory>

#include <SDL2/SDL.h>

#include <Ancona/HAL/Texture.hpp>

namespace ildhal
{

namespace priv
{

struct SDL_TextureDestructor
{
    void operator()(SDL_Texture * t) const { SDL_DestroyTexture(t); }
};

class TextureImpl
{
  public:
    bool LoadSDLTextureFromFile(const std::string & filename, SDL_Renderer & sdlRenderer);

    /* getters and setters */
    SDL_Texture & sdlTexture() const { return *_sdlTexture; }

  private:
    std::unique_ptr<SDL_Texture, SDL_TextureDestructor> _sdlTexture =
        std::unique_ptr<SDL_Texture, SDL_TextureDestructor>(nullptr);
};

} // namespace priv

} // namespace ildhal
