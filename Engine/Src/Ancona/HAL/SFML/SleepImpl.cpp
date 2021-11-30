#include <SFML/System.hpp>

#include <Ancona/HAL/Sleep.hpp>
#include <Ancona/HAL/SFML/TimeImpl.hpp>

namespace ildhal
{

void sleep(const Time & duration)
{
    sf::sleep(duration.timeImpl().sfmlTime());
}

}
