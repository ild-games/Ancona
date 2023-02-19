#include <Ancona/HAL/Music.hpp>
#include <Ancona/HAL/SDL/MusicImpl.hpp>
#include <Ancona/HAL/Time.hpp>
#include <Ancona/System/Log.hpp>

namespace ildhal
{

/* Pimpl Implementation */

bool priv::MusicImpl::LoadSDLMusicFromFile(const std::string & filename)
{
    SDL_RWops * rwops = SDL_RWFromFile(filename.c_str(), "rb");
    if (rwops == nullptr)
    {
        ILD_Log("Failed to SDL_RWops for music!: " << filename << "\nSDL error: " << SDL_GetError());
        return false;
    }
    Mix_Music * loadedMusic = Mix_LoadMUS_RW(rwops, 1);

    if (!loadedMusic)
    {
        ILD_Log("Failed to load music!: " << filename << "\nSDL_mixer error: " << Mix_GetError());
        return false;
    }

    _sdlMusic = std::unique_ptr<Mix_Music, SDL_MusicDestructor>(loadedMusic);

    return true;
}

/* HAL Interface Implementation */

Music::Music()
{
    _pimpl = std::make_unique<priv::MusicImpl>();
}

void Music::Play()
{
    if (Mix_PlayingMusic() == 0)
    {
        Mix_PlayMusic(&musicImpl().sdlMusic(), musicImpl().isLoop() ? -1 : 0);
    }
    else
    {
        Mix_ResumeMusic();
    }
    musicImpl().status(SoundSource::Playing);
}

void Music::Pause()
{
    if (Mix_PausedMusic() == 0)
    {
        Mix_PauseMusic();
    }
    musicImpl().status(SoundSource::Paused);
}

void Music::Stop()
{
    Mix_HaltMusic();
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
    if (Mix_SetMusicPosition(timeOffset.AsSeconds()) < 0)
    {
        ILD_Log("Failed to set music playing offset! SDL_mixer error: " << Mix_GetError());
    }
}

SoundSource::Status Music::status() const
{
    SoundSource::Status status = musicImpl().status();
    if (status == SoundSource::Status::Paused || status == SoundSource::Status::Stopped)
    {
        return status;
    }

    if (Mix_PlayingMusic() == 0)
    {
        musicImpl().status(SoundSource::Status::Stopped);
        return SoundSource::Status::Stopped;
    }

    return SoundSource::Status::Playing;
}

void Music::volume(float volume)
{
    Mix_VolumeMusic((int) (volume * 128));
}

priv::MusicImpl & Music::musicImpl() const
{
    return static_cast<priv::MusicImpl &>(*_pimpl);
}

} // namespace ildhal
