#pragma once

#include <SDL3_mixer/SDL_mixer.h>

#include <Ancona/HAL/SDL/SoundSourceImpl.hpp>
#include <Ancona/HAL/Mixer.hpp>
#include <Ancona/HAL/Sound.hpp>

namespace ildhal
{

namespace priv
{

struct MIX_SoundTrackDestructor
{
    void operator()(MIX_Track* m) const { MIX_DestroyTrack(m); }
};

struct MIX_SoundAudioDestructor
{
    void operator()(MIX_Audio* m) const { MIX_DestroyAudio(m); }
};

class SoundImpl : public SoundSourceImpl
{
  public:
    SoundImpl(
        MIX_Mixer& sdlMixer,
        const ildhal::SoundBuffer& soundBuffer);

    /* getters and setters */
    const ildhal::SoundBuffer * soundBuffer() { return _soundBuffer; }
    MIX_Track & sdlTrack() const { return *_sdlTrack; }
    MIX_Audio & sdlAudio() const { return *_sdlAudio; }

  private:
    const ildhal::SoundBuffer * _soundBuffer;
    std::unique_ptr<MIX_Audio, MIX_SoundAudioDestructor> _sdlAudio =
        std::unique_ptr<MIX_Audio, MIX_SoundAudioDestructor>(nullptr);
    std::unique_ptr<MIX_Track, MIX_SoundTrackDestructor> _sdlTrack = 
        std::unique_ptr<MIX_Track, MIX_SoundTrackDestructor>(nullptr);
};

} // namespace priv

} // namespace ildhal
