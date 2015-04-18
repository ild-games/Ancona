#ifndef Ancona_Util2D_Collision_Math_H_
#define Ancona_Util2D_Collision_Math_H_

#include <utility>
#include <vector>

namespace ild 
{ 

/**
 * @brief Different math functions used for computing if two shapes collide.
 * @author Jeff Swenson
 */
namespace Math
{
    /**
     * @brief A two dimensional point
     */
    typedef std::pair<float, float> Point2;
    /**
     * @brief A shape made up of two dimensional points
     */
    typedef std::vector<Point2> Vertices2;
    /**
     * @brief Used for Normal and Edge vectors
     */
    typedef std::pair<float, float> Vector2;
    /**
     * @brief A projection of a 2D shape into 1D space. It is mapped to a (min, max) pair.
     */
    typedef std::pair<float, float> Projection2;

    /**
     * @brief Simple struct used to return fix information for a collsion.
     * @author Jeff Swenson
     */
    struct CollisionFix
    {
        /**
         * @brief Normal that is the axis used to fix the collision.
         */
        Point2 normal;
        /**
         * @brief Magnitude of the vector needed to push the two shapes apart.
         */
        float magnitude;
    };


    /**
     * @brief Calculate the dot product of the vectors. 
     *
     * @param a The left hand side of the operation.
     * @param b The right hand side of the operation.
     *
     * @return The value of the dot product.
     */
    float Dot(const Math::Vector2 & a, const Math::Vector2 & b);

    /**
     * @brief Create a two dimensional point using the given values.
     *
     * @param sinValue Sin value for the rotation (sin(theta))
     * @param cosValue Cos value for the rotation (cos(theta))
     * @param xSize X distance from the center of the shape.
     * @param ySize y distance from the center of the shape.
     * @param xOffset Difference between the shape center and the origin.
     * @param yOffset Difference between the shape center and the origin.
     *
     * @return A point created using the given information.
     */
    Point2 CreatePoint(
            float sinValue, float cosValue,
            float xSize, float ySize,
            float xOffset, float yOffset);

    /**
     * @brief Calculate the edge vector for two points
     *
     * @param vertexA First point.
     * @param vertexB Second point.
     *
     * @return Edge vector for between the two points.
     */
    Vector2 GetEdge(const Point2 & vertexA, const Point2 & vertexB);

    /**
     * @brief Get a normal vector for the edge.
     *
     * @param edge Edge to calculate the normal vector from.
     *
     * @return Vector normal to the edge.  The vector is not a unit vector.
     */
    Vector2 GetNormal(const Vector2 & edge);

    /**
     * @brief Project a 2D shape into one dimension.  The projection dimension is perpendicular 
     * to the normal vector.  The projection will be accurate if the normal vector is a unit vector.  
     * If the normal vector is not a unit vector then the projection will be skewed.
     *
     * @param shapeA Shape that is being projected.
     * @param normal Vector that is normal to the projection axis.
     *
     * @return Projection into 2d space.  .first is the min value and .second is the max value.
     */
    Projection2 GetProjection(const Vertices2 & shapeA, const Vector2 & normal);

    /**
     * @brief Test if the two projections intersect.
     *
     * @param a First projection to test.
     * @param b Second projection to test.
     *
     * @return True if the projections intersect.  False otherwise.
     */
    bool Intersect(const Projection2 & a, const Projection2 & b);

    /**
     * @brief Normalize the vector so that its magnitude is 1.
     *
     * @param vector Vector to normalize.
     *
     * @return A vector pointing in the same direction as the argument, but with a magnitude of 1.
     */
    Point2 Normalize(const Point2 & vector);

    /**
     * @brief Test if the two shapes collide using the seperating axis theorem.
     *
     * @param shapeA First shape to test.
     * @param shapeB Second shape to test.
     * @param fixVector The vector that can be used to fix the collision. Only valid if the
     * shapes are colliding.
     *
     * @return True if the shapes collide.  False otherwise.
     */
    bool Collide(const Vertices2 & shapeA, const Vertices2 & shapeB, CollisionFix & fixVector);

    /**
     * @brief Test if the two shapes collide using the seperating axis theorem.
     *
     * @param shapeA First shape to test.
     * @param shapeB Second shape to test.
     *
     * @return True if the shapes collide.  False otherwise.
     */
    bool Collide(const Vertices2 & shapeA, const Vertices2 & shapeB);

    /**
     * @brief Get the magnitude of the vector used to seperate the two projections.  The sign of the magnitude
     * will correctly push projection a out of projection b. It will be the minimum absolute value needed to 
     * push the projections apart.
     *
     * @param a A projection of a shape into a single dimension.
     * @param b A projection of a shape into the same dimension.
     *
     * @return A scalar value that will push projection a out of projection b. If they do not overlap then 0
     *  will be returned.
     */
    float FixMagnitude(const Math::Projection2 & a, const Math::Projection2 & b);

    /**
     * @brief Get the fix that would be used to push shapeA out of shapeB using a normal of shapeA.
     *
     * @param shapeA The vertices of a convex shape.
     * @param shapeB The vertices of a convex shape overlapping or adjacent to shapeA.
     *
     * @return The fix that could be used to push shapeA out of shapeB along a normal of shapeA.
     */
    CollisionFix GetFixVector(const Vertices2 & shapeA, const Vertices2 & shapeB);
};

}

#endif
