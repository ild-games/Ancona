#ifndef Ancona_HAL_SFML_MusicImpl_H_
#define Ancona_HAL_SFML_MusicImpl_H_

#include <SFML/Audio.hpp>

#include <Ancona/HAL/SFML/SoundSourceImpl.hpp>

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

}

}

#endif
