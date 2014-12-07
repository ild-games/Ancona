#include <gtest/gtest.h>

#include <cmath>
#include <SFML/System.hpp>

#include <Ancona/Util/Collision/Math.hpp>
#include <Ancona/Util/Collision/Box2.hpp>

using namespace ild;

TEST(CollisionBox2, GetVertices)
{
    Box2 box(sf::Vector2f(),sf::Vector2f(2,2));
    std::vector< std::pair<float,float> > vertices;
    box.GetVertices(vertices);

    auto vertex1 = vertices[0];
    auto vertex2 = vertices[1];
    auto vertex3 = vertices[2];
    auto vertex4 = vertices[3];

    ASSERT_FLOAT_EQ(vertex1.first,1) << "Point 1 X incorrect"; 
    ASSERT_FLOAT_EQ(vertex1.second,1) << "Point 1 Y incorrect"; 

    ASSERT_FLOAT_EQ(vertex2.first,-1) << "Point 2 X incorrect"; 
    ASSERT_FLOAT_EQ(vertex2.second,1) << "Point 2 Y incorrect"; 

    ASSERT_FLOAT_EQ(vertex3.first,-1) << "Point 3 incorrect"; 
    ASSERT_FLOAT_EQ(vertex3.second,-1) << "Point 3 Y incorrect"; 

    ASSERT_FLOAT_EQ(vertex4.first,1) << "Point 4 X incorrect"; 
    ASSERT_FLOAT_EQ(vertex4.second,-1) << "Point 4 Y incorrect"; 
}

TEST(CollisionBox2, GetVerticesWOffset)
{
    Box2 box(sf::Vector2f(10, 14),sf::Vector2f(2,7));
    std::vector< std::pair<float,float> > vertices;
    box.GetVertices(vertices);

    auto vertex1 = vertices[0];
    auto vertex2 = vertices[1];
    auto vertex3 = vertices[2];
    auto vertex4 = vertices[3];

    ASSERT_FLOAT_EQ(vertex1.first,11) << "Point 1 X incorrect"; 
    ASSERT_FLOAT_EQ(vertex1.second,17.5) << "Point 1 Y incorrect"; 

    ASSERT_FLOAT_EQ(vertex2.first,9) << "Point 2 X incorrect"; 
    ASSERT_FLOAT_EQ(vertex2.second,17.5) << "Point 2 Y incorrect"; 

    ASSERT_FLOAT_EQ(vertex3.first,9) << "Point 3 incorrect"; 
    ASSERT_FLOAT_EQ(vertex3.second,10.5) << "Point 3 Y incorrect"; 

    ASSERT_FLOAT_EQ(vertex4.first,11) << "Point 4 X incorrect"; 
    ASSERT_FLOAT_EQ(vertex4.second,10.5) << "Point 4 Y incorrect"; 
}

TEST(CollisionBox2, IntersectsNoOverlap)
{
    Box2 box1(sf::Vector2f(5, 5),sf::Vector2f(2,2));
    Box2 box2(sf::Vector2f(0, 0),sf::Vector2f(3,10));

    Box2 box3(sf::Vector2f(5, 5),sf::Vector2f(9,9));
    Box2 box4(sf::Vector2f(-5, -5),sf::Vector2f(9,9));

    ASSERT_FALSE(box1.Intersects(box2)) << "The two boxes should not intersect";
    ASSERT_FALSE(box3.Intersects(box4)) << "The two boxes should not intersect";
}

TEST(CollisionBox2, IntersectsOverlapSame)
{
    Box2 box1(sf::Vector2f(5, 5),sf::Vector2f(2,2));

    ASSERT_TRUE(box1.Intersects(box1)) << "The two boxes should intersect";
}

TEST(CollisionBox2, IntersectsOverlapDifferent)
{
    Box2 box1(sf::Vector2f(5, 5),sf::Vector2f(2,2));
    Box2 box2(sf::Vector2f(0, 0),sf::Vector2f(10,10));
    Box2 box3(sf::Vector2f(5, 5),sf::Vector2f(1,1));

    ASSERT_TRUE(box1.Intersects(box2)) << "The two boxes should intersect";
    ASSERT_TRUE(box1.Intersects(box3)) << "The two boxes should intersect";
}