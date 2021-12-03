#ifndef Ancona_HAL_SFML_SoundImpl_H_
#define Ancona_HAL_SFML_SoundImpl_H_

#include <SFML/Audio.hpp>

#include <Ancona/HAL/Sound.hpp>
#include <Ancona/HAL/SFML/SoundSourceImpl.hpp>

namespace ildhal
{

namespace priv
{

class SoundImpl : public SoundSourceImpl
{
    public:
        SoundImpl();
        explicit SoundImpl(const sf::SoundBuffer& buffer);

        /* getters and setters */
        sf::Sound & sfmlSound() const { return static_cast<sf::Sound &>(*_sfmlSoundSource); }
};

}

}

#endif
