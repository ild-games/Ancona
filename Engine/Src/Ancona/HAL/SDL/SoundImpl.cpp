#include <memory>

#include <SDL3_mixer/SDL_mixer.h>

#include <Ancona/HAL/SDL/MixerImpl.hpp>
#include <Ancona/HAL/SDL/SoundBufferImpl.hpp>
#include <Ancona/HAL/SDL/SoundImpl.hpp>
#include <Ancona/HAL/SoundBuffer.hpp>
#include <Ancona/System/Log.hpp>
#include <Ancona/Util/Assert.hpp>

namespace ildhal
{

/* Pimpl Implementation */

priv::SoundImpl::SoundImpl(
    MIX_Mixer& sdlMixer,
    const ildhal::SoundBuffer& soundBuffer) : _soundBuffer(&soundBuffer)
{
    MIX_Track* track = MIX_CreateTrack(&sdlMixer);
    if (!track) {
        SDL_Log("Couldn't create a mixer track: %s", SDL_GetError());
        ILD_Assert(false, "SDL3_Mixer MIX_CreateTrack failed"); 
    }

    bool predecode = true;
    bool sdlClosesIo = false;
    SDL_SeekIO(&soundBuffer.soundBufferImpl().sdlIOStream(), 0, SDL_IO_SEEK_SET);
    MIX_Audio* loadedAudio = MIX_LoadAudio_IO(
        &sdlMixer,
        &soundBuffer.soundBufferImpl().sdlIOStream(),
        predecode,
        sdlClosesIo);

    if (!loadedAudio)
    {
        ILD_Log("Failed to load wav sfx! SDL_mixer error: " << SDL_GetError());
        ILD_Log("filename: " << soundBuffer.soundBufferImpl().filename());
        ILD_Assert(false, "SDL3_Mixer MIX_LoadAudio_IO failed"); 
    }
    MIX_SetTrackAudio(track, loadedAudio);

    _sdlAudio = std::unique_ptr<MIX_Audio, MIX_SoundAudioDestructor>(loadedAudio);
    _sdlTrack = std::unique_ptr<MIX_Track, MIX_SoundTrackDestructor>(track);
}

/* HAL Interface Implementation */

Sound::Sound(
    const ildhal::Mixer& mixer,
    const SoundBuffer & buffer)
{
    _pimpl = std::make_unique<priv::SoundImpl>(
        mixer.mixerImpl().sdlMixer(),
        buffer);
}

void Sound::Play()
{
    MIX_PlayTrack(&soundImpl().sdlTrack(), 0);
}

void Sound::Pause()
{
    // noop on SFX
}

void Sound::Stop()
{
    // noop on SFX
}

SoundSource::Status Sound::status() const
{
    // SFX don't need to be queried for status
    return Status::Stopped;
}

void Sound::volume(float volume)
{
    MIX_SetTrackGain(&soundImpl().sdlTrack(), volume);
}

priv::SoundImpl & Sound::soundImpl() const
{
    return static_cast<priv::SoundImpl &>(*_pimpl);
}

} // namespace ildhal
