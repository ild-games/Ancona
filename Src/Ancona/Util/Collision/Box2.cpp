#include<Ancona/Util/Collision/Box2.hpp>
#include<Ancona/Util/Collision/Math.hpp>
#include<Ancona/Util/VectorMath.hpp>

#include<cmath>

using namespace ild;

Box2::Box2(const sf::Vector2f & position,
        const sf::Vector2f & dimmension,
        const float & rotation)
{
    Position = position;
    Dimension = dimmension;
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
    sf::Vector2f fixVector;
    float mag;
    return Intersects(box, fixVector, mag);
}

bool Box2::Intersects(const Box2 & box, sf::Vector2f & fixNormal, float & fixMagnitude) const
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


void Box2::SetPosition(float x, float y)
{
    Position.x = x;
    Position.y = y;
}
