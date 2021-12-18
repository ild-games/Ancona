#include <Ancona/HAL/SFML/ClockImpl.hpp>
#include <Ancona/HAL/Time.hpp>

namespace ildhal
{

/* Pimpl Implementation */

priv::ClockImpl::ClockImpl() : _sfmlClock(std::make_unique<sf::Clock>())
{
}

/* HAL Interface Implementation */
Clock::Clock() : _pimpl(std::make_unique<priv::ClockImpl>())
{
}

Time Clock::ElapsedTime() const
{
    float seconds = clockImpl().sfmlClock().getElapsedTime().asSeconds();
    return ildhal::seconds(static_cast<double>(seconds));
}

Time Clock::Restart()
{
    float seconds = clockImpl().sfmlClock().restart().asSeconds();
    return ildhal::seconds(static_cast<double>(seconds));
}

} // namespace ildhal
