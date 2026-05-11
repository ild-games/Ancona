#pragma once

#include <memory>

#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>

#include <Ancona/HAL/SoundBuffer.hpp>

namespace ildhal
{

namespace priv
{

struct SDL_IOStreamDestructor
{
    void operator()(SDL_IOStream* m) const { SDL_CloseIO(m); }
};

class SoundBufferImpl
{
  public:
    SoundBufferImpl();
    bool LoadSDLAudioFromFile(const std::string& filename);

    /* getters and setters */
    SDL_IOStream& sdlIOStream() const { return *_sdlIOStream; }

  private:
    std::unique_ptr<SDL_IOStream, SDL_IOStreamDestructor> _sdlIOStream;
};

} // namespace priv

} // namespace ildhal
