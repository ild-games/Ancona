#include <memory>

#include <Ancona/HAL/SFML/SoundBufferImpl.hpp>
#include <Ancona/HAL/SFML/SoundImpl.hpp>
#include <Ancona/HAL/SoundBuffer.hpp>

namespace ildhal
{

/* Pimpl Implementation */

priv::SoundImpl::SoundImpl()
{
    _sfmlSoundSource = std::make_unique<sf::Sound>();
}

priv::SoundImpl::SoundImpl(const sf::SoundBuffer &buffer)
{
    _sfmlSoundSource = std::make_unique<sf::Sound>(buffer);
}

/* HAL Interface Implementation */

Sound::Sound()
{
    _pimpl = std::make_unique<priv::SoundImpl>();
}

Sound::Sound(const SoundBuffer &buffer)
{
    const sf::SoundBuffer &sfmlBuffer = buffer.soundBufferImpl().sfmlSoundBuffer();
    _pimpl = std::make_unique<priv::SoundImpl>(sfmlBuffer);
}

void Sound::Play()
{
    soundImpl().sfmlSound().play();
}

void Sound::Pause()
{
    soundImpl().sfmlSound().pause();
}

void Sound::Stop()
{
    soundImpl().sfmlSound().stop();
}

priv::SoundImpl &Sound::soundImpl() const
{
    return static_cast<priv::SoundImpl &>(*_pimpl);
}

} // namespace ildhal
