#include <Ancona/HAL/SDL/SoundBufferImpl.hpp>
#include <Ancona/System/Log.hpp>

namespace ildhal
{

/* Pimpl Implementation */

bool priv::SoundBufferImpl::LoadSDLSoundFromFile(const std::string & filename)
{
    SDL_IOStream * rwops = SDL_IOFromFile(filename.c_str(), "rb");
    if (rwops == nullptr)
    {
        ILD_Log("Failed to SDL_IOStream for sound!: " << filename << "\nSDL error: " << SDL_GetError());
        return false;
    }
    MIX_Audio * loadedSound = MIX_LoadWAV_RW(rwops, 1);

    if (!loadedSound)
    {
        ILD_Log("Failed to load wav sfx!: " << filename << "\nSDL_mixer error: " << SDL_GetError());
        return false;
    }

    _sdlSound = std::unique_ptr<MIX_Audio, SDL_SoundDestructor>(loadedSound);

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
