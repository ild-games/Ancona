#ifndef Ancona_Util_Box2_H_
#define Ancona_Util_Box2_H_

#include <SFML/System.hpp>
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
         * @param position Position of the square
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
        bool Intersects(const Box2 & box);

        /**
         * @brief Test if the box contains the argument box.
         *
         * @param box Box that may be contained.
         *
         * @return True if the box is contained.  False otherwise.
         */
        bool Contains(const Box2 & box);

        /**
         * @brief Test if the two boxes intersect.  Note: Rotation
         * and height of the Box3 is ignored.
         *
         * @param box Box to test intersection on
         *
         * @return True if they intersect.  False otherwise.
         */
        bool Intersects(const Box3 & box);

        /**
         * @brief Test if the box contains the argument box. Note: Rotation
         * and height of the Box3 is ignored.
         *
         * @param box Box that may be contained.
         *
         * @return True if the box is contained.  False otherwise.
         */
        bool Contains(const Box3 & box);
};

}
#endif
