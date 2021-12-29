#pragma once

#include <string>

#include <SDL2_ttf/SDL_ttf.h>

#include <Ancona/HAL/Font.hpp>

namespace ildhal
{

namespace priv
{

struct SDL_FontDestructor
{
    void operator()(TTF_Font * t) const { TTF_CloseFont(t); }
};

class FontImpl
{
  public:
    bool LoadSDLFontFromFile(const std::string & filename);

    /* getters and setters */
    TTF_Font & sdlFont() const { return *_sdlFont; }

  private:
    std::unique_ptr<TTF_Font, SDL_FontDestructor> _sdlFont = std::unique_ptr<TTF_Font, SDL_FontDestructor>(nullptr);
};

} // namespace priv

} // namespace ildhal
