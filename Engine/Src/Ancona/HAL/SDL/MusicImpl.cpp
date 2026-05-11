#include <Ancona/HAL/Music.hpp>
#include <Ancona/HAL/SDL/MixerImpl.hpp>
#include <Ancona/HAL/SDL/MusicImpl.hpp>
#include <Ancona/HAL/Time.hpp>
#include <Ancona/System/Log.hpp>

namespace ildhal
{

/* Pimpl Implementation */

bool priv::MusicImpl::LoadSDLAudioFromFile(
    MIX_Mixer& sdlMixer, 
    const std::string & filename)
{
    SDL_IOStream * rwops = SDL_IOFromFile(filename.c_str(), "rb");
    if (rwops == nullptr)
    {
        ILD_Log("Failed to SDL_IOStream for music!: " << filename << "\nSDL error: " << SDL_GetError());
        return false;
    }

    // TODO maybe `false` for 3rd param, predecode as it will increase load 
    // times and increase RAM usage by predecoding it upon load instead of
    // on demand
    MIX_Audio * loadedAudio = MIX_LoadAudio_IO(&sdlMixer, rwops, true, true);

    if (!loadedAudio)
    {
        ILD_Log("Failed to load audio!: " << filename << "\nSDL_mixer error: " << SDL_GetError());
        return false;
    }

    _sdlAudio = std::unique_ptr<MIX_Audio, MIX_AudioDestructor>(loadedAudio);

    MIX_Track* track = MIX_CreateTrack(&sdlMixer);
    if (!track) {
        SDL_Log("Couldn't create a mixer track: %s", SDL_GetError());
        return false;
    }
    MIX_SetTrackAudio(track, loadedAudio);
    _sdlTrack = std::unique_ptr<MIX_Track, MIX_TrackDesctructor>(track);

    return true;
}

/* HAL Interface Implementation */

Music::Music()
{
    _pimpl = std::make_unique<priv::MusicImpl>();
}

void Music::Play()
{
    if (!MIX_TrackPlaying(&musicImpl().sdlTrack()))
    {
        SDL_PropertiesID options = 0;
        options = SDL_CreateProperties();
        if (!options) {
            SDL_Log("Couldn't create play options: %s", SDL_GetError());
            // TODO error out?
        }
        if (musicImpl().isLoop()) {
            SDL_SetNumberProperty(options, MIX_PROP_PLAY_LOOPS_NUMBER, -1);
        }
        MIX_PlayTrack(&musicImpl().sdlTrack(), options);
    }
    else
    {
        MIX_ResumeTrack(&musicImpl().sdlTrack());
    }
    musicImpl().status(SoundSource::Playing);
}

void Music::Pause()
{
    if (!MIX_TrackPaused(&musicImpl().sdlTrack()))
    {
        MIX_PauseTrack(&musicImpl().sdlTrack());
    }
    musicImpl().status(SoundSource::Paused);
}

void Music::Stop()
{
    MIX_StopTrack(&musicImpl().sdlTrack(), 0);
    musicImpl().status(SoundSource::Stopped);
}

bool Music::OpenFromFile(const ildhal::Mixer& mixer, const std::string& filename)
{
    return musicImpl().LoadSDLAudioFromFile(mixer.mixerImpl().sdlMixer(), filename);
}

/* getters and setters */
void Music::loop(bool newLoop)
{
    musicImpl().isLoop(newLoop);
}

void Music::playingOffset(Time timeOffset)
{
    if (!MIX_SetTrackPlaybackPosition(&musicImpl().sdlTrack(), timeOffset.AsSeconds()))
    {
        ILD_Log("Failed to set music playing offset! SDL_mixer error: " << SDL_GetError());
    }
}

SoundSource::Status Music::status() const
{
    SoundSource::Status status = musicImpl().status();
    if (status == SoundSource::Status::Paused || status == SoundSource::Status::Stopped)
    {
        return status;
    }

    if (!MIX_TrackPlaying(&musicImpl().sdlTrack()))
    {
        musicImpl().status(SoundSource::Status::Stopped);
        return SoundSource::Status::Stopped;
    }

    return SoundSource::Status::Playing;
}

void Music::volume(float volume)
{
    MIX_SetTrackGain(&musicImpl().sdlTrack(), volume);
}

priv::MusicImpl & Music::musicImpl() const
{
    return static_cast<priv::MusicImpl &>(*_pimpl);
}

} // namespace ildhal
