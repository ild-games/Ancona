#pragma once

#include <SFML/Audio.hpp>

#include <Ancona/HAL/SoundBuffer.hpp>

namespace ildhal
{

namespace priv
{

class SoundBufferImpl
{
  public:
    SoundBufferImpl();

    /* getters and setters */
    sf::SoundBuffer & sfmlSoundBuffer() const { return *_sfmlSoundBuffer; }

  private:
    std::unique_ptr<sf::SoundBuffer> _sfmlSoundBuffer;
};

} // namespace priv

} // namespace ildhal
