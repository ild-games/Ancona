#include <Ancona/HAL/SFML/SoundSourceImpl.hpp>

namespace ildhal
{

/* HAL Interface Implementation */

SoundSource::Status SoundSource::status() const
{
    return (SoundSource::Status) soundSourceImpl().sfmlSoundSource().getStatus();
}

void SoundSource::volume(float volume)
{
    soundSourceImpl().sfmlSoundSource().setVolume(volume);
}

}
