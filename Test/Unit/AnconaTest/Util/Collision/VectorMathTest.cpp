#include <gtest/gtest.h>

#include <cmath>

#include <Ancona/Util/VectorMath.hpp>
#include <Ancona/Engine/Core/Systems/Physics/Position.hpp>


using namespace ild;
using namespace ild::VectorMath;

TEST(VectorMath, AboveSquareAngle)
{
    Point left(-3,3);
    Point right(3,3);
    Point between1(0,6);
    Point between2(3,5);
    Point between3(-3,5);
    Point outside1(-3,-3);
    Point outside2(0,-6);
    Point outside3(3,1);

    ASSERT_TRUE(Between(left,right,between1)) << "Should be between";
    ASSERT_TRUE(Between(left,right,between2)) << "Should be between";
    ASSERT_TRUE(Between(left,right,between3)) << "Should be between";

    ASSERT_FALSE(Between(left,right,outside1)) << "Should not be between";
    ASSERT_FALSE(Between(left,right,outside2)) << "Should not be between";
    ASSERT_FALSE(Between(left,right,outside3)) << "Should not be between";
}

TEST(VectorMath, Magnitude)
{
    Point zero(0,0);
    Point unitx(1,0);
    Point unity(0,1);

    ASSERT_NEAR(Magnitude(zero), 0, 0.0001) << "zero vector magnitude incorrect";
    ASSERT_NEAR(Magnitude(unitx), 1, 0.0001) << "Unit vector magnitude incorrect";
    ASSERT_NEAR(Magnitude(unity), 1, 0.0001) << "Unit vector magnitude incorrect";

    Point point1(1,1);
    Point point2(3,-2);
    ASSERT_NEAR(Magnitude(point1), 1.414213562, 0.0001) << "Vector magnitude incorrect";
    ASSERT_NEAR(Magnitude(point2), 3.605551275, 0.0001) << "Vector magnitude incorrect";
}

TEST(VectorMath, Normalize)
{
    Point normalized = Normalize(Point(2,7));
    ASSERT_NEAR(normalized.x, 0.2747, 0.0001) << "X value did not normalize correctly";
    ASSERT_NEAR(normalized.y, 0.9615, 0.0001) << "X value did not normalize correctly";

    normalized = Normalize(Point(-2,7));
    ASSERT_NEAR(normalized.x, -0.2747, 0.0001) << "X value did not normalize correctly";
    ASSERT_NEAR(normalized.y, 0.9615, 0.0001) << "X value did not normalize correctly";

    normalized = Normalize(Point(2,-7));
    ASSERT_NEAR(normalized.x, 0.2747, 0.0001) << "X value did not normalize correctly";
    ASSERT_NEAR(normalized.y, -0.9615, 0.0001) << "X value did not normalize correctly";

    normalized = Normalize(Point(-2,-7));
    ASSERT_NEAR(normalized.x, -0.2747, 0.0001) << "X value did not normalize correctly";
    ASSERT_NEAR(normalized.y, -0.9615, 0.0001) << "X value did not normalize correctly";
}

TEST(VectorMath, PointsTo)
{
    Point pointA(1,7);
    Point pointB(3,5);
    Point vector1(1,-1);
    Point vector2(-1, 3);
    Point vector3 = -vector1;
    Point vector4 = -vector2;

    ASSERT_TRUE(PointsTo(vector1,pointA,pointB)) << "Should point from A to B";
    ASSERT_TRUE(PointsTo(vector4,pointA,pointB)) << "Should point from A to B";

    ASSERT_FALSE(PointsTo(vector3,pointA,pointB)) << "Should not point from A to B";
    ASSERT_FALSE(PointsTo(vector2,pointA,pointB)) << "Should not point from A to B";
}

TEST(VectorMath, RightCollision)
{
    Point pointA(1,2);
    Point pointB(2,3);
    Point vector(-1,0);

    ASSERT_FALSE(PointsTo(vector,pointA,pointB));
}
