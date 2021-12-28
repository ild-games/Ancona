#pragma once

#include <SFML/Audio.hpp>

#include <Ancona/HAL/SDL/SoundSourceImpl.hpp>
#include <Ancona/HAL/Sound.hpp>

namespace ildhal
{

namespace priv
{

class SoundImpl : public SoundSourceImpl
{
  public:
    SoundImpl();
    explicit SoundImpl(const sf::SoundBuffer & buffer);

    /* getters and setters */
    sf::Sound & sfmlSound() const { return static_cast<sf::Sound &>(*_sfmlSoundSource); }
};

} // namespace priv

} // namespace ildhal
