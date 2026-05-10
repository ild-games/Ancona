#include <Ancona/HAL/Music.hpp>
#include <Ancona/HAL/SDL/MusicImpl.hpp>
#include <Ancona/HAL/Time.hpp>
#include <Ancona/System/Log.hpp>

namespace ildhal
{

/* Pimpl Implementation */

bool priv::MusicImpl::LoadSDLMusicFromFile(const std::string & filename)
{
    SDL_IOStream * rwops = SDL_IOFromFile(filename.c_str(), "rb");
    if (rwops == nullptr)
    {
        ILD_Log("Failed to SDL_IOStream for music!: " << filename << "\nSDL error: " << SDL_GetError());
        return false;
    }
    MIX_Audio * loadedMusic = MIX_LoadMUS_RW(rwops, 1);

    if (!loadedMusic)
    {
        ILD_Log("Failed to load music!: " << filename << "\nSDL_mixer error: " << SDL_GetError());
        return false;
    }

    _sdlMusic = std::unique_ptr<MIX_Audio, SDL_MusicDestructor>(loadedMusic);

    return true;
}

/* HAL Interface Implementation */

Music::Music()
{
    _pimpl = std::make_unique<priv::MusicImpl>();
}

void Music::Play()
{
    if (MIX_PlayingMusic() == 0)
    {
        MIX_PlayMusic(&musicImpl().sdlMusic(), musicImpl().isLoop() ? -1 : 0);
    }
    else
    {
        MIX_ResumeMusic();
    }
    musicImpl().status(SoundSource::Playing);
}

void Music::Pause()
{
    if (MIX_PausedMusic() == 0)
    {
        MIX_PauseMusic();
    }
    musicImpl().status(SoundSource::Paused);
}

void Music::Stop()
{
    MIX_HaltMusic();
    musicImpl().status(SoundSource::Stopped);
}

bool Music::OpenFromFile(const std::string & filename)
{
    return musicImpl().LoadSDLMusicFromFile(filename);
}

/* getters and setters */
void Music::loop(bool newLoop)
{
    musicImpl().isLoop(newLoop);
}

void Music::playingOffset(Time timeOffset)
{
    if (MIX_SetMusicPosition(timeOffset.AsSeconds()) < 0)
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

    if (MIX_PlayingMusic() == 0)
    {
        musicImpl().status(SoundSource::Status::Stopped);
        return SoundSource::Status::Stopped;
    }

    return SoundSource::Status::Playing;
}

void Music::volume(float volume)
{
    MIX_VolumeMusic((int) (volume * 128));
}

priv::MusicImpl & Music::musicImpl() const
{
    return static_cast<priv::MusicImpl &>(*_pimpl);
}

} // namespace ildhal
