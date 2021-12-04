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

#ifndef Ancona_HAL_Time_H_
#define Ancona_HAL_Time_H_

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

    float AsSeconds() const;
    int AsMilliseconds() const;
    signed long long AsMicroseconds() const;

    static const Time Zero; ///< Predefined "zero" time value

  private:
    friend Time seconds(float);
    friend Time milliseconds(int);
    friend Time microseconds(signed long long);

    explicit Time(signed long long microseconds);

  private:
    signed long long _microseconds; ///< Time value stored as microseconds
};

Time seconds(float amount);
Time milliseconds(int amount);
Time microseconds(signed long long amount);
Time minTime(Time a, Time b);

bool operator==(Time left, Time right);
bool operator!=(Time left, Time right);
bool operator<(Time left, Time right);
bool operator>(Time left, Time right);
bool operator<=(Time left, Time right);
bool operator>=(Time left, Time right);
Time operator-(Time right);
Time operator+(Time left, Time right);
Time &operator+=(Time &left, Time right);
Time operator-(Time left, Time right);
Time &operator-=(Time &left, Time right);
Time operator*(Time left, float right);
Time operator*(Time left, signed long long right);
Time operator*(float left, Time right);
Time operator*(signed long long left, Time right);
Time &operator*=(Time &left, float right);
Time &operator*=(Time &left, signed long long right);
Time operator/(Time left, float right);
Time operator/(Time left, signed long long right);
Time &operator/=(Time &left, float right);
Time &operator/=(Time &left, signed long long right);
float operator/(Time left, Time right);
Time operator%(Time left, Time right);
Time &operator%=(Time &left, Time right);

} // namespace ildhal

#endif
