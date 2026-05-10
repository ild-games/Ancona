#include <memory>

#include <SDL3_mixer/SDL_mixer.h>

#include <Ancona/HAL/SDL/SoundBufferImpl.hpp>
#include <Ancona/HAL/SDL/SoundImpl.hpp>
#include <Ancona/HAL/SoundBuffer.hpp>

namespace ildhal
{

/* Pimpl Implementation */

priv::SoundImpl::SoundImpl() : _soundBuffer(nullptr)
{
}

priv::SoundImpl::SoundImpl(const ildhal::SoundBuffer & soundBuffer) : _soundBuffer(&soundBuffer)
{
}

/* HAL Interface Implementation */

Sound::Sound()
{
    _pimpl = std::make_unique<priv::SoundImpl>();
}

Sound::Sound(const SoundBuffer & buffer)
{
    _pimpl = std::make_unique<priv::SoundImpl>(buffer);
}

void Sound::Play()
{
    MIX_Audio & sdlSound = soundImpl().soundBuffer()->soundBufferImpl().sdlSound();
    MIX_PlayChannel(-1, &sdlSound, 0);
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
    MIX_Volume(-1, (int) (volume * 128));
}

priv::SoundImpl & Sound::soundImpl() const
{
    return static_cast<priv::SoundImpl &>(*_pimpl);
}

} // namespace ildhal
