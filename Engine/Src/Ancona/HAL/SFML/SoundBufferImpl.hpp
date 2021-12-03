#ifndef Ancona_HAL_SFML_SoundBufferImpl_H_
#define Ancona_HAL_SFML_SoundBufferImpl_H_

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

}

}

#endif
