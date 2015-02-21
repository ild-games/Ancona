#ifndef Ancona_Util_Box2_H_
#define Ancona_Util_Box2_H_

#include <SFML/System.hpp>
#include <vector>
#include <Ancona/Engine/Core/Systems/Physics/Position.hpp>
#include "Box3.hpp"

namespace ild
{

/**
 * @brief Represents a square in 2d space with dimmension, position,
 * and rotation
 * @author Jeff Swenson
 */
class Box2
{
    public:
        /**
         * @brief Create a square
         *
         * @param position Position of the square.  The position is in the center of the square.
         * @param dimmension Dimmension of the square
         * @param rotation Rotation of the square
         */
        Box2(const sf::Vector2f & position,
             const sf::Vector2f & dimmension,
             const float & rotation=0.0f);

        /**
         * @brief Project the box by removing its height.  Note the rotation
         * and height of the argument box is ignored.
         *
         * @param box Box to be projected.
         */
        Box2(const Box3 & box);

        /**
         * @brief Construct a box with zero position and rotation.
         *
         * @param dimX Size in the X dimmension.
         * @param dimY Size in the Y dimmension.
         */
        Box2(float dimX, float dimY);

        /**
         * @brief Set the position of the box to the given value.
         *
         * @param x X position.
         * @param y Y position.
         */
        void SetPosition(float x, float y);

        /**
         * @brief Position of the box.  The position is located at the center.
         */
        sf::Vector2f Position;
        /**
         * @brief Dimmension of the box:  Length X Width
         */
        sf::Vector2f Dimmension;
        /**
         * @brief The rotation of the box.
         */
        float Rotation;

        /**
         * @brief Test if the two boxes intersect
         *
         * @param box Box to test intersection on
         *
         * @return True if they intersect.  False otherwise.
         */
        bool Intersects(const Box2 & box) const;

        /**
         * @brief Test if the two boxes intersect
         *
         * @param box Box to test intersection on
         * @param fixVector Vector that will push the calling box out of the argument box.
         *
         * @return True if they intersect.  False otherwise.
         */
        bool Intersects(const Box2 & box, sf::Vector2f & fixVector) const;

        /**
         * @brief Clear the vertices vector and fill it with vertices for the box.
         *
         * @param vertices A vector used as an output parameter for the vertices.
         */
        void GetVertices(std::vector< std::pair<float,float> > & vertices) const;
};

}
#endif
