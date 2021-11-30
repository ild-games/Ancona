#include <Ancona/HAL/SFML/TimeImpl.hpp>

namespace ildhal
{

/* Pimpl Implementation */

priv::TimeImpl::TimeImpl() :
    _sfmlTime(std::make_unique<sf::Time>())
{
}

priv::TimeImpl::TimeImpl(float seconds) :
    _sfmlTime(std::make_unique<sf::Time>(sf::seconds(seconds)))
{
}

/* HAL Interface Implementation */

Time::Time() :
    _pimpl(std::make_unique<priv::TimeImpl>())
{
}

Time::Time(float seconds) :
    _pimpl(std::make_unique<priv::TimeImpl>(seconds))
{
}

float Time::AsSeconds() const
{
    return timeImpl().sfmlTime().asSeconds();
}

Time seconds(float amount)
{
    Time time(amount);
    return time;
}

}
