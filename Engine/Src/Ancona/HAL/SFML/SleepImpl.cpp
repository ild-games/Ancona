#include <SFML/System.hpp>

#include <Ancona/HAL/Sleep.hpp>
#include <Ancona/HAL/Time.hpp>

namespace ildhal
{

void sleep(const Time &duration)
{
    sf::sleep(sf::microseconds(duration.AsMicroseconds()));
}

} // namespace ildhal
