#include <Ancona/Util2D/Collision/Box2.hpp>
#include <Ancona/Util2D/VectorMath.hpp>
#include <Ancona/Util/Assert.hpp>

#define _USE_MATH_DEFINES
#include <cmath>

using namespace ild;

namespace DoesIntersect {
    enum Enum {
        Yes,
        No,
        Maybe
    };
}

#include <iostream>
DoesIntersect::Enum OptimizedIntersectRotated(const Box2 & left, const Box2 & right) {
    /**
    * If the boxes are rotated, we know that the radius of the box is less than the two dimensions added together. If
    * the circules formed by the radius don't overlap, then we know the boxes don't overlap.
    */
    auto leftPosition = sf::Vector2f(left.TopLeft().first, left.TopLeft().second);
    auto rightPosition = sf::Vector2f(right.TopLeft().first, right.TopLeft().second);

    auto radiusLeft = left.Dimension.x + left.Dimension.y;
    auto radiusRight = right.Dimension.x + right.Dimension.y;
    auto positionDiff = leftPosition - rightPosition;

    auto totalRadius = radiusLeft * radiusLeft + radiusRight * radiusRight;
    auto distance = positionDiff.x * positionDiff.x + positionDiff.y * positionDiff.y;

    if (totalRadius < distance) {
        return DoesIntersect::No;
    }
    return DoesIntersect::Maybe;
}

DoesIntersect::Enum OptimizedIntersectAligned(const Box2 & left, const Box2 & right) {
    /**
    * Normally we compute intersection using the SAT algorithm. That allows us to handle all convex shapes. The SAT
    * algorithm allows for complex collision detection, but it is a little slow. This implementation is an optimization
    * for non-rotated boxes. Useing this optimization was measured to improve the overall collision performance by an order
    * of magnitude.
    */
    auto leftXMin = left.Position.x;
    auto leftXMax = leftXMin + left.Dimension.x;
    auto rightXMin = right.Position.x;
    auto rightXMax = rightXMin + right.Dimension.x;
    if (leftXMax < rightXMin || rightXMax < leftXMin)
    {
        return DoesIntersect::No;
    }

    auto leftYMin = left.Position.y;
    auto leftYMax = leftYMin + left.Dimension.y;
    auto rightYMin = right.Position.y;
    auto rightYMax = rightYMin + right.Dimension.y;
    if (leftYMax < rightYMin || rightYMax < leftYMin)
    {
        return DoesIntersect::No;
    }

    return DoesIntersect::Yes;
}

DoesIntersect::Enum OptimizedIntersect(const Box2 & left, const Box2 & right)
{
    if (left.Rotation != 0.0f || right.Rotation != 0.0f) {
        return OptimizedIntersectRotated(left, right);
    } else {
        return OptimizedIntersectAligned(left, right);
    }
}

Box2::Box2(
    const sf::Vector2f & position,
    const sf::Vector2f & dimension,
    const sf::Vector2f & anchor,
    const float & rotation)
{
    Position = position;
    Dimension = dimension;
    Anchor = anchor;
    Rotation = rotation;
}

Box2::Box2(float dimX, float dimY)
    : Box2(sf::Vector2f(),sf::Vector2f(dimX,dimY))
{

}

void Box2::GetVertices(std::vector< std::pair<float, float> > & vertices) const
{
    vertices.clear();
    vertices.push_back(BotRight());
    vertices.push_back(BotLeft());
    vertices.push_back(TopLeft());
    vertices.push_back(TopRight());
}

bool Box2::Intersects(const Box2 & box) const
{
    auto intersects = OptimizedIntersect(*this, box);
    if (intersects == DoesIntersect::Maybe)
    {
        sf::Vector2f fixVector;
        float mag;
        return SATCollision(box, fixVector, mag);
    }
    return intersects == DoesIntersect::Yes;
}


bool Box2::Intersects(const Box2 & box, sf::Vector2f & fixNormal, float & fixMagnitude) const
{
    if (OptimizedIntersect(*this, box) == DoesIntersect::No)
    {
        fixNormal.x = 0;
        fixNormal.y = 0;
        fixMagnitude = 0;
        return false;
    }

    return SATCollision(box, fixNormal, fixMagnitude);
}

bool Box2::SATCollision(const Box2 & box, sf::Vector2f & fixNormal, float & fixMagnitude) const
{
    static Math::Vertices2 verticesA;
    static Math::Vertices2 verticesB;

    GetVertices(verticesA);
    box.GetVertices(verticesB);

    Math::CollisionFix fix;
    bool collides = Math::Collide(verticesA,verticesB,fix);

    fixNormal.x = fix.normal.first;
    fixNormal.y = fix.normal.second;

    fixMagnitude = fix.magnitude;

    return collides;
}

sf::Vector2f Box2::GetNormalOfCollisionEdge(const Box2 & box) const
{
    Math::Vertices2 verticesA;
    Math::Vertices2 verticesB;

    GetVertices(verticesA);
    box.GetVertices(verticesB);

    Math::CollisionFix fix = Math::GetFixVector(verticesA, verticesB);

    sf::Vector2f normal(fix.normal.first,fix.normal.second);

    if(!VectorMath::PointsTo(normal, Position, box.Position))
    {
        normal *= -1.0f;
    }

    return normal;
}


void Box2::position(float x, float y)
{
    Position.x = x;
    Position.y = y;
}
