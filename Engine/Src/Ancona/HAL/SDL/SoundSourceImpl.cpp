#include <Ancona/HAL/SDL/SoundSourceImpl.hpp>

namespace ildhal
{

/* HAL Interface Implementation */

SoundSource::Status SoundSource::status() const
{
    return SoundSource::Status::Stopped;
}

void SoundSource::volume(float volume)
{
}

} // namespace ildhal
