#include <Ancona/Util/Timer.hpp>

using namespace ild;

float Timer::_elapsedTime = 0.0f;
float Timer::_startTime = 0.0f;

void Timer::Update(float delta)
{
    Timer::_elapsedTime += delta;
}

void Timer::Restart()
{
    Timer::_startTime = Timer::_elapsedTime;
}

float Timer::AsMilliseconds()
{
    return (Timer::_elapsedTime - Timer::_startTime) * 1000.0f;
}

void Timer::SetMilliseconds(float millis)
{
    Timer::_elapsedTime = millis / 1000.0f;
    Timer::_startTime = 0.0f;
}
