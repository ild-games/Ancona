#ifndef Ancona_Util_Collision_Math_H_
#define Ancona_Util_Collision_Math_H_

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
     * @brief A two dimmensional point
     */
    typedef std::pair<float, float> Point2;
    /**
     * @brief A shape made up of two dimmensional points
     */
    typedef std::vector<Point2> Vertices2;
    /**
     * @brief Used for Normal and Edge vectors
     */
    typedef std::pair<float, float> Vector2;
    /**
     * @brief A projection of a 2D shape into 1D space
     */
    typedef std::pair<float, float> Projection2;

    /**
     * @brief Create a two dimmensional point using the given values.
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
     * @brief Project a 2D shape into one dimmension.  The projection dimmension is perpendicular 
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
     * @brief Test if the two shapes collide using the seperating axis theorem.
     *
     * @param shapeA First shape to test.
     * @param shapeB Second shape to test.
     *
     * @return True if the shapes collide.  False otherwise.
     */
    bool Collide(const Vertices2 & shapeA, const Vertices2 & shapeB);
};

}

#endif
