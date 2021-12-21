// Altered SFML Time.hpp for Ancona's HAL abstraction layer

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

#pragma once

#include <cstdint>

namespace ildhal
{

namespace priv
{
class TimeImpl;
}

class Time
{
  public:
    Time();

    double AsSeconds() const;
    int AsMilliseconds() const;
    int64_t AsMicroseconds() const;

    static const Time Zero; ///< Predefined "zero" time value

  private:
    friend Time seconds(double);
    friend Time milliseconds(int);
    friend Time microseconds(int64_t);

    explicit Time(int64_t microseconds);

  private:
    int64_t _microseconds; ///< Time value stored as microseconds
};

Time seconds(double amount);
Time milliseconds(int amount);
Time microseconds(int64_t amount);
Time minTime(Time a, Time b);

bool operator==(Time left, Time right);
bool operator!=(Time left, Time right);
bool operator<(Time left, Time right);
bool operator>(Time left, Time right);
bool operator<=(Time left, Time right);
bool operator>=(Time left, Time right);
Time operator-(Time right);
Time operator+(Time left, Time right);
Time & operator+=(Time & left, Time right);
Time operator-(Time left, Time right);
Time & operator-=(Time & left, Time right);
Time operator*(Time left, double right);
Time operator*(Time left, int64_t right);
Time operator*(double left, Time right);
Time operator*(int64_t left, Time right);
Time & operator*=(Time & left, double right);
Time & operator*=(Time & left, int64_t right);
Time operator/(Time left, double right);
Time operator/(Time left, int64_t right);
Time & operator/=(Time & left, double right);
Time & operator/=(Time & left, int64_t right);
double operator/(Time left, Time right);
Time operator%(Time left, Time right);
Time & operator%=(Time & left, Time right);

} // namespace ildhal
