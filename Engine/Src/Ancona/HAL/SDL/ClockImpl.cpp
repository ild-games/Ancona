#include <SDL2/SDL.h>

#include <Ancona/HAL/SDL/ClockImpl.hpp>
#include <Ancona/HAL/Time.hpp>
#include <Ancona/System/Log.hpp>

namespace ildhal
{

/* Pimpl Implementation */

priv::ClockImpl::ClockImpl() : _clockStartTicks(SDL_GetPerformanceCounter())
{
}

/* HAL Interface Implementation */
Clock::Clock() : _pimpl(std::make_unique<priv::ClockImpl>())
{
}

Time Clock::ElapsedTime() const
{
    uint64_t currentTicks = SDL_GetPerformanceCounter();
    double seconds = static_cast<double>(
        (currentTicks - clockImpl().clockStartTicks()) / static_cast<double>(SDL_GetPerformanceFrequency()));

    return ildhal::seconds(seconds);
}

Time Clock::Restart()
{
    auto time = Clock::ElapsedTime();
    clockImpl().clockStartTicks(SDL_GetPerformanceCounter());
    return time;
}

} // namespace ildhal
