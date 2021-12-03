#ifndef Ancona_HAL_SFML_ClockImpl_H_
#define Ancona_HAL_SFML_ClockImpl_H_

#include <SFML/System.hpp>

#include <Ancona/HAL/Clock.hpp>

namespace ildhal
{

namespace priv
{

class ClockImpl
{
  public:
    ClockImpl();

    /* getters and setters */
    sf::Clock &sfmlClock() const
    {
        return *_sfmlClock;
    }

  private:
    std::unique_ptr<sf::Clock> _sfmlClock;
};

} // namespace priv

} // namespace ildhal

#endif
