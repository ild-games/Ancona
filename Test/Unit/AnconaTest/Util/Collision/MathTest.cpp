#include <gtest/gtest.h>

#include <cmath>

#include <Ancona/Util/Collision/Math.hpp>


using namespace ild::Math;

TEST(CollisionMath, CreatePointNoRotation)
{
   auto point1 = CreatePoint(0,1,5,10,0,0); 
   auto point2 = CreatePoint(0,1,5,10,10,100); 

   ASSERT_EQ(point1.first, 5) <<  "X with no offset set incorrectly";
   ASSERT_EQ(point1.second, 10) << "Y with no offset set incorrectly";

   ASSERT_EQ(point2.first, 15) << "X with offset set incorrectly";
   ASSERT_EQ(point2.second, 110) << "Y with offset set incorrectly";
}

TEST(CollisionMath, CreatePointWithUnitRotation)
{
    auto angle1 = 30 * M_PI / 180;
    auto angle2 = 45 * M_PI / 180;
    auto point1 = CreatePoint(sin(angle1),cos(angle1),10,10,0,0);
    auto point2 = CreatePoint(sin(angle1),cos(angle1),10,10,10,100);
    auto point3 = CreatePoint(sin(angle2),cos(angle2),10,10,0,0);
    auto point4 = CreatePoint(sin(angle2),cos(angle2),10,10,10,100);

    ASSERT_FLOAT_EQ(point1.first, 3.660254) << "X rotated 30 degrees calculated incorrectly";
    ASSERT_FLOAT_EQ(point1.second, 13.660254) << "Y rotated 30 degrees calculated incorrectly";

    ASSERT_FLOAT_EQ(point2.first, 13.660254) << "X w/offset rotated 30 degrees calculated incorrectly";
    ASSERT_FLOAT_EQ(point2.second, 113.660254) << "Y w/offset rotated 30 degrees calculated incorrectly";

    ASSERT_FLOAT_EQ(point3.first, 0) << "X rotated 45 degrees calculated incorrectly";
    ASSERT_FLOAT_EQ(point3.second, 14.142136) << "Y rotated 45 degrees calculated incorrectly";

    ASSERT_FLOAT_EQ(point4.first, 10) << "X w/offset rotated 45 degrees calculated incorrectly";
    ASSERT_FLOAT_EQ(point4.second, 114.142136) << "Y w/offset rotated 45 degrees calculated incorrectly";
}

TEST(CollisionMath, CreatePointWithUnusualRotation)
{
    auto angle = 33 * M_PI / 180;
    auto point = CreatePoint(sin(angle),cos(angle),13,27,100,10);

    ASSERT_FLOAT_EQ(point.first,-3.802537 + 100) << "X rotated incorrectly";
    ASSERT_FLOAT_EQ(point.second,29.724413 + 10) << "Y rotated incorrectly";
}

TEST(CollisionMath, GetEdge)
{
    Point2 pointA(15, 3); 
    Point2 pointB(7, 10); 
    auto edge = GetEdge(pointA,pointB);

    ASSERT_FLOAT_EQ(edge.first, 8) << "X calculated incorrectly";
    ASSERT_FLOAT_EQ(edge.second, -7) << "Y calculated incorrectly";
}

TEST(CollisionMath, GetProjectionTriangle)
{
    Point2 pointA(2,4); 
    Point2 pointB(10,5); 
    Point2 pointC(5,10); 

    Vertices2 triangle;
    triangle.push_back(pointA);
    triangle.push_back(pointB);
    triangle.push_back(pointC);

    Vector2 dimmx(1,0);
    Vector2 dimmy(0,1);

    auto projectionX = GetProjection(triangle, dimmx); 
    auto projectionY = GetProjection(triangle, dimmy); 

    ASSERT_FLOAT_EQ(projectionX.first, 2) << "X Projection: min incorrect";
    ASSERT_FLOAT_EQ(projectionX.second, 10) << "X Projection: max incorrect";

    ASSERT_FLOAT_EQ(projectionY.first, 4) << "Y Projection: min incorrect";
    ASSERT_FLOAT_EQ(projectionY.second, 10) << "Y Projection: max incorrect";
}

TEST(CollisionMath, GetProjectionTraingle)
{
    Point2 pointA(2,4); 
    Point2 pointB(2,3); 
    Point2 pointC(10,5); 
    Point2 pointD(6,11); 

    Vertices2 square;
    square.push_back(pointA);
    square.push_back(pointB);
    square.push_back(pointC);
    square.push_back(pointD);

    Vector2 dimmx(1,0);
    Vector2 dimmy(0,1);

    auto projectionX = GetProjection(square, dimmx); 
    auto projectionY = GetProjection(square, dimmy); 

    ASSERT_FLOAT_EQ(projectionX.first, 2) << "X Projection: min incorrect";
    ASSERT_FLOAT_EQ(projectionX.second, 10) << "X Projection: max incorrect";

    ASSERT_FLOAT_EQ(projectionY.first, 3) << "Y Projection: min incorrect";
    ASSERT_FLOAT_EQ(projectionY.second, 11) << "Y Projection: max incorrect";
}
