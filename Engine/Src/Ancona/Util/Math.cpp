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

float Math::DistanceBetween(sf::Vector2f startPoint, sf::Vector2f endPoint)
{
    return std::sqrt(std::pow(endPoint.x - startPoint.x, 2) + std::pow(endPoint.y - startPoint.y, 2));
}