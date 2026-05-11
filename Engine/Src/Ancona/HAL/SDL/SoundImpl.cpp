#include <memory>

#include <SDL3_mixer/SDL_mixer.h>

#include <Ancona/HAL/SDL/MixerImpl.hpp>
#include <Ancona/HAL/SDL/SoundBufferImpl.hpp>
#include <Ancona/HAL/SDL/SoundImpl.hpp>
#include <Ancona/HAL/SoundBuffer.hpp>

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
        // TODO throw error?
    }

    // TODO maybe `false` for 3rd param, predecode as it will increase load 
    // times and increase RAM usage by predecoding it upon load instead of
    // on demand
    MIX_Audio* loadedAudio = MIX_LoadAudio_IO(
        &sdlMixer,
        &soundBuffer.soundBufferImpl().sdlIOStream(),
        true,
        true);

    if (!loadedAudio)
    {
        SDL_Log("Failed to load wav sfx!\nSDL_mixer error: %s", SDL_GetError());
        // TODO throw error?
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
