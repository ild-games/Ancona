#define _USE_MATH_DEFINES
#include <cmath>

#include <Ancona/Util2D/VectorMath.hpp>

namespace ild
{
namespace VectorMath
{

float Magnitude(const Vector2f &vector)
{
    return sqrt(vector.x * vector.x + vector.y * vector.y);
}

Vector2f Normalize(const Vector2f &vector)
{
    auto magnitude = Magnitude(vector);
    return Vector2f(vector.x / magnitude, vector.y / magnitude);
}

Vector2f Rotate(Vector2f vectToRotate, float rads)
{
    float newX, newY;
    newX = (vectToRotate.x * cos(rads)) - (vectToRotate.y * sin(rads));
    newY = (vectToRotate.x * sin(rads)) + (vectToRotate.y * cos(rads));
    Vector2f toReturn(newX, newY);
    return toReturn;
}

Vector3f Rotate(Vector3f vectToRotate, float rads)
{
    float newX, newY, newZ = 0;
    newX = (vectToRotate.x * cos(rads)) - (vectToRotate.y * sin(rads));
    newY = (vectToRotate.x * sin(rads)) + (vectToRotate.y * cos(rads));
    Vector3f toReturn(newX, newY, newZ);
    return toReturn;
}

Vector2f ComponentMultiplication(Vector2f lhs, Vector2f rhs)
{
    return Vector2f(lhs.x * rhs.x, lhs.y * rhs.y);
}

Vector3f ComponentMultiplication(Vector3f lhs, Vector3f rhs)
{
    return Vector3f(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
}

float DegreesToRadians(float degrees)
{
    return degrees * (M_PI / 180);
}

float RadiansToDegrees(float rads)
{
    return rads * (180 / M_PI);
}

float Cross(const Vector2f &left, const Vector2f right)
{
    return left.x * right.y - left.y * right.x;
}

bool PointsTo(const Vector2f &vector, const Vector2f &positionA, const Vector2f &positionB)
{
    auto diff = positionB - positionA;
    decltype(diff) norm1(-diff.y, diff.x);
    decltype(diff) norm2(diff.y, -diff.x);

    return Cross(vector, norm1) >= 0 && Cross(vector, norm2) <= 0;
}

bool Between(const Vector2f &leftBound, const Vector2f &rightBound, const Vector2f &middle)
{
    auto &a = leftBound;
    auto &b = middle;
    auto &c = rightBound;

    return Cross(a, b) * Cross(a, c) >= 0 && Cross(c, b) * Cross(c, a) >= 0;
}
} // namespace VectorMath
} // namespace ild
