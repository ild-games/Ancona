#include <cmath>

#include <gtest/gtest.h>

#include <Ancona/Util2D/Collision/Math.hpp>


using namespace ild::Math;

TEST(CollisionMath, GetNormal)
{
    Point2 value(10,7);
    ASSERT_EQ(Point2(-7,10),GetNormal(value)) << "Normal is not created correctly";
}

TEST(CollisionMath, RotatePointNoRotation)
{
   auto point1 = RotatePoint(std::pair<float, float>(5, 10),std::pair<float, float>(0, 0), 0);

   ASSERT_EQ(point1.first, 5) <<  "X with no rotation set incorrectly";
   ASSERT_EQ(point1.second, 10) << "Y with no rotation set incorrectly";
}

TEST(CollisionMath, RotatePointWithRotation)
{
    auto angle1 = 30 * M_PI / 180;
    auto angle2 = 45 * M_PI / 180;
    auto point1 = RotatePoint(std::pair<float, float>(10, 10), std::pair<float, float>(0, 0), angle1);
    auto point2 = RotatePoint(std::pair<float, float>(10, 10), std::pair<float, float>(0, 0), angle2);

    ASSERT_FLOAT_EQ(point1.first, 3.660254) << "X rotated 30 degrees calculated incorrectly";
    ASSERT_FLOAT_EQ(point1.second, 13.660254) << "Y rotated 30 degrees calculated incorrectly";

    ASSERT_FLOAT_EQ(point2.first, 0) << "X rotated 45 degrees calculated incorrectly";
    ASSERT_FLOAT_EQ(point2.second, 14.142136) << "Y rotated 45 degrees calculated incorrectly";
}

TEST(CollisionMath, RotatePointWithUnusualRotation)
{
    auto angle = 33 * M_PI / 180;
    auto point = RotatePoint(std::pair<float, float>(13, 27), std::pair<float, float>(0, 0), angle);

    ASSERT_FLOAT_EQ(point.first, -3.802537) << "X rotated incorrectly";
    ASSERT_FLOAT_EQ(point.second, 29.724413) << "Y rotated incorrectly";
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

TEST(CollisionMath, FixMagnitudeNonOverlapping)
{
    std::string msg = "The projections are incorrectly identified as overallping";
    ASSERT_EQ(0,FixMagnitude(Point2(3,6),Point2(7,9))) << msg;
    ASSERT_EQ(0,FixMagnitude(Point2(3,6),Point2(6,9))) << msg;
    ASSERT_EQ(0,FixMagnitude(Point2(3,6),Point2(-1,3))) << msg;
    ASSERT_EQ(0,FixMagnitude(Point2(3,6),Point2(-1,2))) << msg;
}

TEST(CollisionMath, FixMagnitudeOverlapping)
{
    std::string msg = "The fix vector returned was not the smallest vector that will push A out of B";
    ASSERT_EQ(-1,FixMagnitude(Point2(3,6),Point2(5,9)));
    ASSERT_EQ( 2,FixMagnitude(Point2(3,6),Point2(-1,5)));
}

TEST(CollisionMath, FixMagnitudeContained)
{
    std::string msg = "The fix vector returned was not correct for contained values";
    ASSERT_EQ(-5, FixMagnitude(Point2(2,6),Point2(1,8))) << msg;
    ASSERT_EQ( 5, FixMagnitude(Point2(3,7),Point2(1,8))) << msg;

    ASSERT_EQ( 5, FixMagnitude(Point2(1,8),Point2(2,6))) << msg;
    ASSERT_EQ(-5, FixMagnitude(Point2(1,8),Point2(3,7))) << msg;
}

TEST(CollisionMath, VectorNormalize)
{
    Point2 normalized = Normalize(Point2(2,7));
    ASSERT_NEAR(normalized.first, 0.2747, 0.0001) << "X value did not normalize correctly";
    ASSERT_NEAR(normalized.second, 0.9615, 0.0001) << "X value did not normalize correctly";

    normalized = Normalize(Point2(-2,7));
    ASSERT_NEAR(normalized.first, -0.2747, 0.0001) << "X value did not normalize correctly";
    ASSERT_NEAR(normalized.second, 0.9615, 0.0001) << "X value did not normalize correctly";

    normalized = Normalize(Point2(2,-7));
    ASSERT_NEAR(normalized.first, 0.2747, 0.0001) << "X value did not normalize correctly";
    ASSERT_NEAR(normalized.second, -0.9615, 0.0001) << "X value did not normalize correctly";

    normalized = Normalize(Point2(-2,-7));
    ASSERT_NEAR(normalized.first, -0.2747, 0.0001) << "X value did not normalize correctly";
    ASSERT_NEAR(normalized.second, -0.9615, 0.0001) << "X value did not normalize correctly";
}
