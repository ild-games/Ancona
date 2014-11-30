#include<Ancona/Util/Space/Box2.hpp>

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

std::pair<float,float> createPoint(float sinV, float cosV, float xSize, float ySize, float xOffset, float yOffset)
{
    float xPos = xSize * cosV - ySize * sinV + xOffset;
    float yPos = xSize * sinV + ySize * cosV + yOffset; 

    return std::pair<float,float>(xPos,yPos);
}

void Box2::GetVertices(std::vector< std::pair<float,float> > & vertices)
{
    vertices.clear();

    float sinV = sin(Rotation);
    float cosV = cos(Rotation);

    float xSize = Dimmension.x / 2;
    float ySize = Dimmension.y / 2;

    float xOffset = Position.x;
    float yOffset = Position.y;

    vertices.push_back(createPoint(sinV,cosV, xSize, ySize, xOffset, yOffset));
    vertices.push_back(createPoint(sinV,cosV, -xSize, ySize, xOffset, yOffset));
    vertices.push_back(createPoint(sinV,cosV, -xSize, -ySize, xOffset, yOffset));
    vertices.push_back(createPoint(sinV,cosV, xSize, -ySize, xOffset, yOffset));
}
