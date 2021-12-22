#include <Ancona/HAL/SDL/SoundBufferImpl.hpp>

namespace ildhal
{

/* Pimpl Implementation */

priv::SoundBufferImpl::SoundBufferImpl() : _sfmlSoundBuffer(std::make_unique<sf::SoundBuffer>())
{
}

/* HAL Interface Implementation */

SoundBuffer::SoundBuffer() : _pimpl(std::make_unique<priv::SoundBufferImpl>())
{
}

bool SoundBuffer::LoadFromFile(const std::string & filename, ildhal::RenderTarget & target)
{
    return soundBufferImpl().sfmlSoundBuffer().loadFromFile(filename);
}

} // namespace ildhal