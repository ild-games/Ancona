#pragma once

#include <memory>

#include <SDL2/SDL_mixer.h>

#include <Ancona/HAL/SoundBuffer.hpp>

namespace ildhal
{

namespace priv
{

struct SDL_SoundDestructor
{
    void operator()(Mix_Chunk * m) const { Mix_FreeChunk(m); }
};

class SoundBufferImpl
{
  public:
    bool LoadSDLSoundFromFile(const std::string & filename);

    /* getters and setters */
    Mix_Chunk & sdlSound() const { return *_sdlSound; }

  private:
    std::unique_ptr<Mix_Chunk, SDL_SoundDestructor> _sdlSound =
        std::unique_ptr<Mix_Chunk, SDL_SoundDestructor>(nullptr);
};

} // namespace priv

} // namespace ildhal
