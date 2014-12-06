#include<Ancona/Util/Collision/Box2.hpp>
#include<Ancona/Util/Collision/Math.hpp>

#include<cmath>

using namespace ild;

Box2::Box2(const sf::Vector2f & position,
        const sf::Vector2f & dimmension,
        const float & rotation)
{
    Position = position;
    Dimmension = dimmension;
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

    float xSize = Dimmension.x / 2;
    float ySize = Dimmension.y / 2;

    float xOffset = Position.x;
    float yOffset = Position.y;

    vertices.push_back(Math::CreatePoint(sinV,cosV, xSize, ySize, xOffset, yOffset));
    vertices.push_back(Math::CreatePoint(sinV,cosV, -xSize, ySize, xOffset, yOffset));
    vertices.push_back(Math::CreatePoint(sinV,cosV, -xSize, -ySize, xOffset, yOffset));
    vertices.push_back(Math::CreatePoint(sinV,cosV, xSize, -ySize, xOffset, yOffset));
}

bool Box2::Intersects(const Box2 & box) const
{
    Math::Vertices2 verticesA;
    Math::Vertices2 verticesB;

    GetVertices(verticesA);
    box.GetVertices(verticesB);

    return Math::Collide(verticesA,verticesB);
}

void Box2::SetPosition(float x, float y)
{
    Position.x = x;
    Position.y = y;
}
