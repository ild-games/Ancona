#ifndef Ancona_Util_Math_H_
#define Ancona_Util_Math_H_

namespace ild
{

namespace Math
{
template <typename T>
int signum(T val)
{
    return (T(0) < val) - (val < T(0));
}

float DegreesToRadians(float degrees);
float RadiansToDegrees(float rads);
}

}

#endif