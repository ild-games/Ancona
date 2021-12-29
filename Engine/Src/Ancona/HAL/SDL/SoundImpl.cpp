#include <memory>

#include <Ancona/HAL/SDL/SoundBufferImpl.hpp>
#include <Ancona/HAL/SDL/SoundImpl.hpp>
#include <Ancona/HAL/SoundBuffer.hpp>

namespace ildhal
{

/* Pimpl Implementation */

/* HAL Interface Implementation */

Sound::Sound()
{
    _pimpl = std::make_unique<priv::SoundImpl>();
}

Sound::Sound(const SoundBuffer & buffer)
{
    _pimpl = std::make_unique<priv::SoundImpl>();
}

void Sound::Play()
{
}

void Sound::Pause()
{
}

void Sound::Stop()
{
}

priv::SoundImpl & Sound::soundImpl() const
{
    return static_cast<priv::SoundImpl &>(*_pimpl);
}

} // namespace ildhal
