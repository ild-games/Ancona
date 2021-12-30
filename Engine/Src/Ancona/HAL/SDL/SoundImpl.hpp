#pragma once

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
    SoundImpl(const ildhal::SoundBuffer & soundBuffer);

    /* getters and setters */
    const ildhal::SoundBuffer * soundBuffer() { return _soundBuffer; }

  private:
    const ildhal::SoundBuffer * _soundBuffer;
};

} // namespace priv

} // namespace ildhal
