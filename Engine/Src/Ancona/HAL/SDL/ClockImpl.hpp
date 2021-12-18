#pragma once

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
    uint64_t clockStartTicks() const { return _clockStartTicks; }
    void clockStartTicks(uint64_t newClockStartTicks) { _clockStartTicks = newClockStartTicks; }

  private:
    uint64_t _clockStartTicks = 0;
};

} // namespace priv

} // namespace ildhal
