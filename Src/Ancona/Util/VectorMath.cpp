#include <Ancona/Util/VectorMath.hpp>

#include <math.h>

using namespace ild;

namespace ild
{
namespace VectorMath
{

float Magnitude(const sf::Vector2f & vector)
{
    return sqrt(vector.x * vector.x + vector.y * vector.y);
}

sf::Vector2f Normalize(const sf::Vector2f & vector)
{
    auto magnitude = Magnitude(vector);  
    return sf::Vector2f(vector.x / magnitude, vector.y / magnitude);
}

sf::Vector2f Rotate(sf::Vector2f vectToRotate, float rads)
{
    float newX, newY;
    newX = (vectToRotate.x * cos(rads)) - (vectToRotate.y * sin(rads));
    newY = (vectToRotate.x * sin(rads)) + (vectToRotate.y * cos(rads));
    sf::Vector2f toReturn(newX, newY);
    return toReturn;
}

sf::Vector3f Rotate(sf::Vector3f vectToRotate, float rads)
{
    float newX, newY, newZ = 0;
    newX = (vectToRotate.x * cos(rads)) - (vectToRotate.y * sin(rads));
    newY = (vectToRotate.x * sin(rads)) + (vectToRotate.y * cos(rads));
    sf::Vector3f toReturn(newX, newY, newZ);
    return toReturn;
}

float DegreesToRadians(float degrees)
{
    return degrees * (M_PI / 180);
}

float RadiansToDegrees(float rads)
{
    return rads * (180 / M_PI);
}

float Cross(const sf::Vector2f & left, const sf::Vector2f right)

{
    return left.x * right.y - left.y * right.x;
}

bool Between(const sf::Vector2f & leftBound, const sf::Vector2f & rightBound, const sf::Vector2f & middle)
{
    auto & a = leftBound;
    auto & b = middle;
    auto & c = rightBound;

    return Cross(a,b) * Cross(a,c) >= 0 && Cross(c,b) * Cross(c,a) >= 0;
}
}
}
