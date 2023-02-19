#include <Ancona/HAL/SDL/SoundBufferImpl.hpp>
#include <Ancona/System/Log.hpp>

namespace ildhal
{

/* Pimpl Implementation */

bool priv::SoundBufferImpl::LoadSDLSoundFromFile(const std::string & filename)
{
    SDL_RWops * rwops = SDL_RWFromFile(filename.c_str(), "rb");
    if (rwops == nullptr)
    {
        ILD_Log("Failed to SDL_RWops for sound!: " << filename << "\nSDL error: " << SDL_GetError());
        return false;
    }
    Mix_Chunk * loadedSound = Mix_LoadWAV_RW(rwops, 1);

    if (!loadedSound)
    {
        ILD_Log("Failed to load wav sfx!: " << filename << "\nSDL_mixer error: " << Mix_GetError());
        return false;
    }

    _sdlSound = std::unique_ptr<Mix_Chunk, SDL_SoundDestructor>(loadedSound);

    return true;
}

/* HAL Interface Implementation */

SoundBuffer::SoundBuffer() : _pimpl(std::make_unique<priv::SoundBufferImpl>())
{
}

bool SoundBuffer::LoadFromFile(const std::string & filename, ildhal::RenderTarget & target)
{
    return soundBufferImpl().LoadSDLSoundFromFile(filename);
}

} // namespace ildhal
