#ifndef Ancona_HAL_SFML_MusicImpl_H_
#define Ancona_HAL_SFML_MusicImpl_H_

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

#endif