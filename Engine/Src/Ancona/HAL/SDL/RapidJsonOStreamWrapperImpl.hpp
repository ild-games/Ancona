#pragma once

#include <string>

#include <SDL2/SDL.h>

#include <Ancona/HAL/RapidJsonOStreamWrapper.hpp>

namespace ildhal
{

namespace priv
{

class RapidJsonOStreamWrapperImpl
{
  public:
    bool LoadFromFile(const std::string & filename);

    /* getters and setters */
    SDL_RWops & sdlRwops() const { return *_sdlRwops; }

  private:
    SDL_RWops * _sdlRwops = nullptr;
};

} // namespace priv

} // namespace ildhal
