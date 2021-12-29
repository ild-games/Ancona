#include <Ancona/HAL/Music.hpp>
#include <Ancona/HAL/SDL/MusicImpl.hpp>
#include <Ancona/HAL/Time.hpp>

namespace ildhal
{

/* Pimpl Implementation */

priv::MusicImpl::MusicImpl()
{
}

/* HAL Interface Implementation */

Music::Music()
{
    _pimpl = std::make_unique<priv::MusicImpl>();
}

void Music::Play()
{
}

void Music::Pause()
{
}

void Music::Stop()
{
}

bool Music::OpenFromFile(const std::string & filename)
{
    return true;
}

/* getters and setters */
void Music::loop(bool newLoop)
{
}

void Music::playingOffset(Time timeOffset)
{
}

priv::MusicImpl & Music::musicImpl() const
{
    return static_cast<priv::MusicImpl &>(*_pimpl);
}

} // namespace ildhal
