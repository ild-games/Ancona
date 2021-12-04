// Altered version of SFML's Time.cpp for Ancona's HAL compatibility layer

////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2018 Laurent Gomila (laurent@sfml-dev.org)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////
#include <algorithm>

#include <Ancona/HAL/Time.hpp>

namespace ildhal
{

const Time Time::Zero;

/* HAL Interface Implementation */

Time::Time() : _microseconds(0)
{
}

float Time::AsSeconds() const
{
    return _microseconds / 1000000.f;
}
int Time::AsMilliseconds() const
{
    return static_cast<int>(_microseconds / 1000);
}
signed long long Time::AsMicroseconds() const
{
    return _microseconds;
}

Time::Time(signed long long microseconds) : _microseconds(microseconds)
{
}

Time seconds(float amount)
{
    return Time(static_cast<signed long long>(amount * 1000000));
}

Time milliseconds(int amount)
{
    return Time(static_cast<signed long long>(amount) * 1000);
}
Time microseconds(signed long long amount)
{
    return Time(amount);
}
Time minTime(Time a, Time b)
{
    return seconds(std::min(a.AsSeconds(), b.AsSeconds()));
}

bool operator==(Time left, Time right)
{
    return left.AsMicroseconds() == right.AsMicroseconds();
}
bool operator!=(Time left, Time right)
{
    return left.AsMicroseconds() != right.AsMicroseconds();
}
bool operator<(Time left, Time right)
{
    return left.AsMicroseconds() < right.AsMicroseconds();
}
bool operator>(Time left, Time right)
{
    return left.AsMicroseconds() > right.AsMicroseconds();
}
bool operator<=(Time left, Time right)
{
    return left.AsMicroseconds() <= right.AsMicroseconds();
}
bool operator>=(Time left, Time right)
{
    return left.AsMicroseconds() >= right.AsMicroseconds();
}
Time operator-(Time right)
{
    return microseconds(-right.AsMicroseconds());
}
Time operator+(Time left, Time right)
{
    return microseconds(left.AsMicroseconds() + right.AsMicroseconds());
}
Time &operator+=(Time &left, Time right)
{
    return left = left + right;
}
Time operator-(Time left, Time right)
{
    return microseconds(left.AsMicroseconds() - right.AsMicroseconds());
}
Time &operator-=(Time &left, Time right)
{
    return left = left - right;
}
Time operator*(Time left, float right)
{
    return seconds(left.AsSeconds() * right);
}
Time operator*(Time left, signed long long right)
{
    return microseconds(left.AsMicroseconds() * right);
}
Time operator*(float left, Time right)
{
    return right * left;
}
Time operator*(signed long long left, Time right)
{
    return right * left;
}
Time &operator*=(Time &left, float right)
{
    return left = left * right;
}
Time &operator*=(Time &left, signed long long right)
{
    return left = left * right;
}
Time operator/(Time left, float right)
{
    return seconds(left.AsSeconds() / right);
}
Time operator/(Time left, signed long long right)
{
    return microseconds(left.AsMicroseconds() / right);
}
Time &operator/=(Time &left, float right)
{
    return left = left / right;
}
Time &operator/=(Time &left, signed long long right)
{
    return left = left / right;
}
float operator/(Time left, Time right)
{
    return left.AsSeconds() / right.AsSeconds();
}
Time operator%(Time left, Time right)
{
    return microseconds(left.AsMicroseconds() % right.AsMicroseconds());
}
Time &operator%=(Time &left, Time right)
{
    return left = left % right;
}

} // namespace ildhal
