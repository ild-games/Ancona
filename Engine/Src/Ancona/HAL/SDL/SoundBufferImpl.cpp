#include <Ancona/HAL/SDL/SoundBufferImpl.hpp>
#include <Ancona/System/Log.hpp>

namespace ildhal
{

/* Pimpl Implementation */

priv::SoundBufferImpl::SoundBufferImpl() : 
    _sdlIOStream(std::unique_ptr<SDL_IOStream, SDL_IOStreamDestructor>(nullptr))
{
}

bool priv::SoundBufferImpl::LoadSDLAudioFromFile(
    const std::string & filename)
{
    SDL_IOStream * iostream = SDL_IOFromFile(filename.c_str(), "rb");
    if (iostream == nullptr)
    {
        ILD_Log("Failed to SDL_IOStream for sound!: " << filename << "\nSDL error: " << SDL_GetError());
        return false;
    }
    _sdlIOStream = std::unique_ptr<SDL_IOStream, SDL_IOStreamDestructor>(iostream);

    return true;
}

/* HAL Interface Implementation */

SoundBuffer::SoundBuffer() : _pimpl(std::make_unique<priv::SoundBufferImpl>())
{
}

bool SoundBuffer::LoadFromFile(
    const std::string & filename,
    ildhal::RenderTarget & target)
{
    return soundBufferImpl().LoadSDLAudioFromFile(filename);
}

} // namespace ildhal
