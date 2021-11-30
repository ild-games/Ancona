#ifndef Ancona_Util2D_VectorMath_H_
#define Ancona_Util2D_VectorMath_H_

#include <Ancona/Util/Vector2.hpp>
#include <Ancona/Util/Vector3.hpp>

namespace ild
{

namespace VectorMath
{
    /**
     * @brief Normalize the vector.
     *
     * @param vector Vector to normalize.
     *
     * @return A normalized vector pointing in th same direction.
     */
    Vector2f Normalize(const Vector2f & vector);

    /**
     * @brief Calculate the magnitude of the vector.
     *
     * @param vector Vector to calculate the magnitude of.
     *
     * @return magnitude of the vector.
     */
    float Magnitude(const Vector2f & vector);

    /**
     * @brief Return a Vector2f that is rotated a given amount of
     *        radians from a given source vector.
     *
     * @param vectToRotate Vector2f to rotate.
     * @param rads Amount in radians to rotate the vector.
     *
     * @return A Vector2f that is rotated from the source vector.
     */
    Vector2f Rotate(Vector2f vectToRotate, float rads);

    /**
     * @brief Return a Vector3f that is rotated a given amount of
     *        radians from a given source vector.
     *
     * @param vectToRotate Vector3f to rotate.
     * @param rads Amount in radians to rotate the vector.
     *
     * @return A Vector3f that is rotated from the source vector.
     */
    Vector3f Rotate(Vector3f vectToRotate, float rads);

    /**
     * @brief Return a Vector2f where each component is multiplied by the
     *        same component as another Vector2f
     *
     * @param lhs Vector2f used on left hand side of equation
     * @param rhs Vector2f used on right hand side of equation
     *
     * @return Resulting Vector2f
     */
    Vector2f ComponentMultiplication(Vector2f lhs, Vector2f rhs);

    /**
     * @brief Return a Vector2f where each component is multiplied by the
     *        same component as another Vector2f
     *
     * @param lhs Vector2f used on left hand side of equation
     * @param rhs Vector2f used on right hand side of equation
     *
     * @return Resulting Vector2f
     */
    Vector3f ComponentMultiplication(Vector3f lhs, Vector3f rhs);

    /**
     * @brief Test if the middle vector within the small angle between left and right bound vectors.
     *
     * @param leftBound Vector that is the left bound.  
     * @param rightBound Vector that is the right bound. 
     * @param middle Vector that is being tested to be between the left and the right bound.
     *
     * @return True if the middle vector is between the right and left bounds.
     */
    bool Between(const Vector2f & leftBound, const Vector2f & rightBound, const Vector2f & middle);

    /**
     * @brief Produce the 2d cross product.
     *
     * @param left Left operand.
     * @param right Right operand.
     *
     * @return The cross product.
     */
    float Cross(const Vector2f & left, const Vector2f right);

    /**
     * @brief Convert degrees to radians.
     *
     * @param degrees Degree to convert.
     *
     * @return Radians converted from degrees.
     */
    float DegreesToRadians(float degrees);


    /**
     * @brief Determine if the vector points in the direction of positionB
     * from positionA.  It points in the direction of positionB if it is
     * pointing to the correct hemisphere.
     *
     * @param vector Vector that is being tested for direction.
     * @param positionA Position that is the root.
     * @param positionB Position that is being pointed to.
     *
     * @return True if the vector points from positionA to positionB.
     */
    bool PointsTo(const Vector2f & vector,const Vector2f & positionA,const Vector2f & positionB);

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
