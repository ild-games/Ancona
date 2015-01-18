#include <Ancona/Util/VectorMath.hpp>

#include <math.h>

using namespace ild;

sf::Vector2f vector::Rotate(sf::Vector2f vectToRotate, float rads)
{
    float newX, newY;
    newX = (vectToRotate.x * cos(rads)) - (vectToRotate.y * sin(rads));
    newY = (vectToRotate.x * sin(rads)) + (vectToRotate.y * cos(rads));
    sf::Vector2f toReturn(newX, newY);
    return toReturn;
}

//TODO
sf::Vector3f vector::Rotate(sf::Vector3f vectToRotate, float rads)
{
    float newX, newY, newZ = 0;
    newX = (vectToRotate.x * cos(rads)) - (vectToRotate.y * sin(rads));
    newY = (vectToRotate.x * sin(rads)) + (vectToRotate.y * cos(rads));
    sf::Vector3f toReturn(newX, newY, newZ);
    return toReturn;
}

float vector::DegreesToRadians(float degrees)
{
    return degrees * (M_PI / 180);
}

float vector::RadiansToDegrees(float rads)
{
    return rads * (180 / M_PI);
}
