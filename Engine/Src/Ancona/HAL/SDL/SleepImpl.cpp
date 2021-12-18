#include <SDL2/SDL.h>

#include <Ancona/HAL/Sleep.hpp>
#include <Ancona/HAL/Time.hpp>

namespace ildhal
{

void sleep(const Time & duration)
{
    if (duration >= Time::Zero)
    {
        SDL_Delay(duration.AsMilliseconds());
    }
}

} // namespace ildhal
