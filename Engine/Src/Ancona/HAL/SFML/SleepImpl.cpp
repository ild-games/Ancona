#include <SFML/System.hpp>

#include <Ancona/HAL/SFML/TimeImpl.hpp>
#include <Ancona/HAL/Sleep.hpp>

namespace ildhal
{

void sleep(const Time &duration)
{
    sf::sleep(duration.timeImpl().sfmlTime());
}

} // namespace ildhal
