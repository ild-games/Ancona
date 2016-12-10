#include <cmath>

#include <Ancona/Util/Math.hpp>

using namespace ild;


float Math::DegreesToRadians(float degrees)
{
    return degrees * (M_PI / 180);
}

float Math::RadiansToDegrees(float rads)
{
    return rads * (180 / M_PI);
}
