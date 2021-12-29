#include <Ancona/HAL/SDL/SoundBufferImpl.hpp>

namespace ildhal
{

/* Pimpl Implementation */

priv::SoundBufferImpl::SoundBufferImpl()
{
}

/* HAL Interface Implementation */

SoundBuffer::SoundBuffer() : _pimpl(std::make_unique<priv::SoundBufferImpl>())
{
}

bool SoundBuffer::LoadFromFile(const std::string & filename, ildhal::RenderTarget & target)
{
    return true;
}

} // namespace ildhal
