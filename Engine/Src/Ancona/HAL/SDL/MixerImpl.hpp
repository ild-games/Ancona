#pragma once

#include <memory>

#include <Ancona/HAL/Mixer.hpp>
#include <SDL3_mixer/SDL_mixer.h>

namespace ildhal
{

namespace priv
{

struct MIX_MixerDestructor
{
    void operator()(MIX_Mixer* t) const { MIX_DestroyMixer(t); }
};

class MixerImpl
{
  public:
    MixerImpl(MIX_Mixer* mixer);

    /* getters and setters */
    MIX_Mixer& sdlMixer() const { return *_sdlMixer; }

  private:
    std::unique_ptr<MIX_Mixer, MIX_MixerDestructor> _sdlMixer = 
        std::unique_ptr<MIX_Mixer, MIX_MixerDestructor>(nullptr);
};

} // namespace priv

} // namespace ildhal
