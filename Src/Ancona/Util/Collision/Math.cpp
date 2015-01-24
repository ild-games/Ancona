#include <Ancona/Util/Collision/Math.hpp>
#include <cmath>

using namespace ild;

std::pair<float,float> Math::CreatePoint(
        float sinValue, float cosValue,
        float xSize, float ySize,
        float xOffset, float yOffset)
{
    float xPos = xSize * cosValue - ySize * sinValue + xOffset;
    float yPos = xSize * sinValue + ySize * cosValue + yOffset; 

    return std::pair<float,float>(xPos,yPos);
}

Math::Vector2 Math::GetEdge(const Point2 & vertexA, const Point2 & vertexB)
{
    return Vector2(vertexA.first - vertexB.first, vertexA.second - vertexB.second);
}

Math::Vector2 Math::GetNormal(const Vector2 & edge)
{
    return Vector2(-edge.second, edge.first);
}


float Dot(const Math::Vector2 & a, const Math::Vector2 & b)
{
    return a.first * b.first + a.second * b.second;        
}

Math::Projection2 Math::GetProjection(const Vertices2 & shapeA, const Vector2 & normal)
{
    auto max = -INFINITY;
    auto min = INFINITY;

    for(auto & point : shapeA)
    {
        auto dot = Dot(point, normal);
        max = fmax(max, dot);
        min = fmin(min, dot);
    }
    
    return Projection2(min,max);
}

bool Math::Intersect(const Projection2 & a, const Projection2 & b)
{
    return !(a.first > b.second || b.first > a.second);   
}


//Only test the axis's defined by shapeA
bool TestShapeAxis(const Math::Vertices2 & shapeA, const Math::Vertices2 & shapeB)
{
    using namespace Math;
    for(int i = 0; i < shapeA.size(); i++)
    {
        auto endIndex = i + 1 >= shapeA.size() ? 0 : i + 1;
        auto edge = GetEdge(shapeA[i], shapeA[endIndex]);
        auto normal = GetNormal(edge);

        auto projectionA = GetProjection(shapeA, normal);
        auto projectionB = GetProjection(shapeB, normal);

        if(!Intersect(projectionA, projectionB))
        {
            return false; 
        }
    }
    return true;
}

bool Math::Collide(const Vertices2 & shapeA, const Vertices2 & shapeB)
{
    return TestShapeAxis(shapeA,shapeB) &&
        TestShapeAxis(shapeB,shapeA);
}
