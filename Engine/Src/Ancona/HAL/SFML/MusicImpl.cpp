#include <Ancona/HAL/Music.hpp>
#include <Ancona/HAL/SFML/MusicImpl.hpp>
#include <Ancona/HAL/SFML/TimeImpl.hpp>

namespace ildhal
{

/* Pimpl Implementation */

priv::MusicImpl::MusicImpl()
{
    _sfmlSoundSource = std::make_unique<sf::Music>();
}

sf::Music &priv::MusicImpl::sfmlMusic() const
{
    return static_cast<sf::Music &>(*_sfmlSoundSource);
}

/* HAL Interface Implementation */

Music::Music()
{
    _pimpl = std::make_unique<priv::MusicImpl>();
}

void Music::Play()
{
    musicImpl().sfmlMusic().play();
}

void Music::Pause()
{
    musicImpl().sfmlMusic().pause();
}

void Music::Stop()
{
    musicImpl().sfmlMusic().stop();
}

bool Music::OpenFromFile(const std::string &filename)
{
    return musicImpl().sfmlMusic().openFromFile(filename);
}

/* getters and setters */
void Music::loop(bool newLoop)
{
    musicImpl().sfmlMusic().setLoop(newLoop);
}

void Music::playingOffset(Time timeOffset)
{
    musicImpl().sfmlMusic().setPlayingOffset(sf::seconds(timeOffset.AsSeconds()));
}

priv::MusicImpl &Music::musicImpl() const
{
    return static_cast<priv::MusicImpl &>(*_pimpl);
}

} // namespace ildhal
