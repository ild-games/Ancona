#ifndef Ancona_Util_VectorMath_H_
#define Ancona_Util_VectorMath_H_

#include <SFML/System.hpp>

namespace ild
{

namespace vector
{

    /**
     * @brief Return a Vector2f that is rotated a given amount of
     *        radians from a given source vector.
     *
     * @param vectToRotate Vector2f to rotate.
     * @param rads Amount in radians to rotate the vector.
     *
     * @return A Vector2f that is rotated from the source vector.
     */
    sf::Vector2f Rotate(sf::Vector2f vectToRotate, float rads);

    /**
     * @brief Return a Vector3f that is rotated a given amount of
     *        radians from a given source vector.
     *
     * @param vectToRotate Vector3f to rotate.
     * @param rads Amount in radians to rotate the vector.
     *
     * @return A Vector3f that is rotated from the source vector.
     */
    sf::Vector3f Rotate(sf::Vector3f vectToRotate, float rads);

    /**
     * @brief Convert degrees to radians.
     *
     * @param degrees Degree to convert.
     *
     * @return Radians converted from degrees.
     */
    float DegreesToRadians(float degrees);

    /**
     * @brief Convert radians to degrees.
     *
     * @param rads Radians to convert.
     *
     * @return Degrees converted from radians.
     */
    float RadiansToDegrees(float rads);
}

}

#endif
