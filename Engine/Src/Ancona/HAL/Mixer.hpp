
#pragma once

namespace ildhal
{

namespace priv
{
class MixerImpl;
}

class Mixer
{
  public:
    Mixer();

    /* getters and setters */
    priv::MixerImpl & mixerImpl() const;

  private:
    std::unique_ptr<priv::MixerImpl> _pimpl;
};

} // namespace ildhal
