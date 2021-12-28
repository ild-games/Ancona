#pragma once

#include <SFML/Audio.hpp>

#include <Ancona/HAL/SoundSource.hpp>

namespace ildhal
{

namespace priv
{

class SoundSourceImpl
{
  public:
    /* getters and setters */
    sf::SoundSource & sfmlSoundSource() const { return *_sfmlSoundSource; }

  protected:
    std::unique_ptr<sf::SoundSource> _sfmlSoundSource;
};

} // namespace priv

} // namespace ildhal
