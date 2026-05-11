#pragma once

#include <memory>

#include <SDL3_mixer/SDL_mixer.h>

#include <Ancona/HAL/SDL/SoundSourceImpl.hpp>

namespace ildhal
{

namespace priv
{

struct MIX_TrackDesctructor
{
    void operator()(MIX_Track* m) const { MIX_DestroyTrack(m); }
};

struct MIX_AudioDestructor
{
    void operator()(MIX_Audio* m) const { MIX_DestroyAudio(m); }
};

class MusicImpl : public SoundSourceImpl
{
  public:
    bool LoadSDLAudioFromFile(MIX_Mixer& sdlMixer, const std::string & filename);

    /* getters and setters */
    void isLoop(bool newIsLoop) { _isLoop = newIsLoop; }
    bool isLoop() const { return _isLoop; }
    void status(const SoundSource::Status & newStatus) { _status = newStatus; }
    const SoundSource::Status & status() const { return _status; }

    MIX_Audio & sdlAudio() const { return *_sdlAudio; }
    MIX_Track & sdlTrack() const { return *_sdlTrack; }

  private:
    bool _isLoop = false;
    SoundSource::Status _status = SoundSource::Status::Stopped;

    std::unique_ptr<MIX_Audio, MIX_AudioDestructor> _sdlAudio =
        std::unique_ptr<MIX_Audio, MIX_AudioDestructor>(nullptr);
    std::unique_ptr<MIX_Track, MIX_TrackDesctructor> _sdlTrack = 
        std::unique_ptr<MIX_Track, MIX_TrackDesctructor>(nullptr);
};

} // namespace priv

} // namespace ildhal
