#include <Ancona/HAL/SFML/ClockImpl.hpp>
#include <Ancona/HAL/SFML/TimeImpl.hpp>

namespace ildhal
{

/* Pimpl Implementation */

priv::ClockImpl::ClockImpl() :
    _sfmlClock(std::make_unique<sf::Clock>())
{
}

/* HAL Interface Implementation */
Clock::Clock() :
    _pimpl(std::make_unique<priv::ClockImpl>())
{
}

Time Clock::ElapsedTime() const
{
    auto seconds = clockImpl().sfmlClock().getElapsedTime().asSeconds();
    return ildhal::seconds(seconds);
}

Time Clock::Restart()
{
    auto seconds = clockImpl().sfmlClock().restart().asSeconds();
    return ildhal::seconds(seconds);
}

}
