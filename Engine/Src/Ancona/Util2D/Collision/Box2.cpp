#include<Ancona/Util2D/Collision/Box2.hpp>
#include<Ancona/Util2D/Collision/Math.hpp>
#include<Ancona/Util2D/VectorMath.hpp>

#include<cmath>

using namespace ild;

namespace DoesIntersect {
    enum Enum {
        Yes,
        No,
        Maybe
    };
}

DoesIntersect::Enum OptimizedIntersect(const Box2 & left, const Box2 & right)
{
    /**
     * Normally we compute intersection using the SAT algorithm. That allows us to handle all convex shapes. The SAT
     * algorithm allows for complex collision detection, but it is a little slow. This implementation is an optimization
     * for non-rotated boxes. Useing this optimization was measured to improve the overall collision performance by an order
     * of magnitude.
     */
    if (left.Rotation != 0.0f || right.Rotation != 0.0f)
    {
        return DoesIntersect::Maybe;
    }

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

Box2::Box2(const sf::Vector2f & position,
        const sf::Vector2f & dimension,
        const float & rotation)
{
    Position = position;
    Dimension = dimension;
    Rotation = rotation;
}

Box2::Box2(float dimX, float dimY)
    : Box2(sf::Vector2f(),sf::Vector2f(dimX,dimY))
{

}

void Box2::GetVertices(std::vector< std::pair<float,float> > & vertices) const
{
    vertices.clear();

    float sinV = sin(Rotation);
    float cosV = cos(Rotation);

    float xSize = Dimension.x / 2;
    float ySize = Dimension.y / 2;

    float xOffset = Position.x;
    float yOffset = Position.y;

    vertices.push_back(Math::CreatePoint(sinV,cosV, xSize, ySize, xOffset, yOffset));
    vertices.push_back(Math::CreatePoint(sinV,cosV, -xSize, ySize, xOffset, yOffset));
    vertices.push_back(Math::CreatePoint(sinV,cosV, -xSize, -ySize, xOffset, yOffset));
    vertices.push_back(Math::CreatePoint(sinV,cosV, xSize, -ySize, xOffset, yOffset));
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
    Math::Vertices2 verticesA;
    Math::Vertices2 verticesB;

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
