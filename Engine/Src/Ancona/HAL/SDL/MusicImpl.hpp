#pragma once

#include <memory>

#include <SDL2/SDL_mixer.h>

#include <Ancona/HAL/SDL/SoundSourceImpl.hpp>

namespace ildhal
{

namespace priv
{

struct SDL_MusicDestructor
{
    void operator()(Mix_Music * m) const { Mix_FreeMusic(m); }
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

    Mix_Music & sdlMusic() const { return *_sdlMusic; }

  private:
    bool _isLoop = false;
    SoundSource::Status _status = SoundSource::Status::Stopped;

    std::unique_ptr<Mix_Music, SDL_MusicDestructor> _sdlMusic =
        std::unique_ptr<Mix_Music, SDL_MusicDestructor>(nullptr);
};

} // namespace priv

} // namespace ildhal
