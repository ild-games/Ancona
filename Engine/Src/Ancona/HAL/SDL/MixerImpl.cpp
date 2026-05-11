#include <Ancona/HAL/SDL/MixerImpl.hpp>
#include <Ancona/System/Log.hpp>
#include <Ancona/Util/Assert.hpp>

namespace ildhal
{

/* Pimpl Implementation */

priv::MixerImpl::MixerImpl(MIX_Mixer * sdlMixer) : _sdlMixer(sdlMixer)
{
}

/* HAL Interface Implementation */

Mixer::Mixer()
{
    MIX_Mixer* mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);
    // ILD_ReleaseAssert
    //     !mixer,
    //     "SDL_Mixer couldn't create mixer on default device! SDL_mixer error: " << SDL_GetError());
    _pimpl = std::make_unique<priv::MixerImpl>(mixer);
}

/* getters and setters */
priv::MixerImpl& Mixer::mixerImpl() const
{
    return static_cast<priv::MixerImpl &>(*_pimpl);
}

} // namespace ildhal
