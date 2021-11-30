#ifndef Ancona_Util_Math_H_
#define Ancona_Util_Math_H_

#include <Ancona/Util/Vector2.hpp>

namespace ild {

namespace Math {

template <typename T>
int signum(T val) {
    return (T(0) < val) - (val < T(0));
}

float DegreesToRadians(float degrees);
float RadiansToDegrees(float rads);
float Distance(const Vector2f & startPoint, const Vector2f & endPoint);

}

}

#endif
