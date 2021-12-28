#pragma once

#include <SFML/Audio.hpp>

#include <Ancona/HAL/SDL/SoundSourceImpl.hpp>

namespace ildhal
{

namespace priv
{

class MusicImpl : public SoundSourceImpl
{
  public:
    MusicImpl();

    /* getters and setters */
    sf::Music & sfmlMusic() const;
};

} // namespace priv

} // namespace ildhal
