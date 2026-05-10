#pragma once

#include <memory>

#include <SDL3_mixer/SDL_mixer.h>

#include <Ancona/HAL/SoundBuffer.hpp>

namespace ildhal
{

namespace priv
{

struct SDL_SoundDestructor
{
    void operator()(MIX_Audio * m) const { MIX_DestroyAudio(m); }
};

class SoundBufferImpl
{
  public:
    bool LoadSDLSoundFromFile(const std::string & filename);

    /* getters and setters */
    MIX_Audio & sdlSound() const { return *_sdlSound; }

  private:
    std::unique_ptr<MIX_Audio, SDL_SoundDestructor> _sdlSound =
        std::unique_ptr<MIX_Audio, SDL_SoundDestructor>(nullptr);
};

} // namespace priv

} // namespace ildhal
