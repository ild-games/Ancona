#pragma once

#include <memory>

#include <SDL3_mixer/SDL_mixer.h>

#include <Ancona/HAL/SDL/SoundSourceImpl.hpp>

namespace ildhal
{

namespace priv
{

struct SDL_MusicDestructor
{
    void operator()(MIX_Audio * m) const { MIX_DestroyAudio(m); }
};

class MusicImpl : public SoundSourceImpl
{
  public:
    bool LoadSDLMusicFromFile(const std::string & filename);

    /* getters and setters */
    void isLoop(bool newIsLoop) { _isLoop = newIsLoop; }
    bool isLoop() const { return _isLoop; }
    void status(const SoundSource::Status & newStatus) { _status = newStatus; }
    const SoundSource::Status & status() const { return _status; }

    MIX_Audio & sdlMusic() const { return *_sdlMusic; }

  private:
    bool _isLoop = false;
    SoundSource::Status _status = SoundSource::Status::Stopped;

    std::unique_ptr<MIX_Audio, SDL_MusicDestructor> _sdlMusic =
        std::unique_ptr<MIX_Audio, SDL_MusicDestructor>(nullptr);
};

} // namespace priv

} // namespace ildhal
