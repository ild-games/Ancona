#ifndef Ancona_Util2D_Box3_H_
#define Ancona_Util2D_Box3_H_

#include <Ancona/Util/Vector2.hpp>
#include <Ancona/Util/Vector3.hpp>

namespace ild
{

/**
 * @brief Represents a box in 3rd space with a dimension, position,
 * and rotation
 * @author Jeff Swenson
 */
class Box3
{
    public:
        /**
         * @brief Initialize a 3 dimensional box
         *
         * @param position The position of the box
         * @param dimension The size of the box
         * @param rotation The rotation of the box
         */
        Box3(const Vector3f & position,
             const Vector3f & dimension,
             const Vector2f & rotation = Vector2f());

        /**
         * @brief Position of the box.  The position is at the center
         * of the box.
         */
        Vector3f Position;
        /**
         * @brief Dimension of the box: Length X Width X Height
         */
        Vector3f Dimension;
        /**
         * @brief The rotation of the box.
         */
        Vector2f Rotation;

        /**
         * @brief Test if the two boxes intersect
         *
         * @param box Box to be tested
         *
         * @return True if they intersect.  False otherwise.
         */
        bool Intersects(const Box3 & box);

        /**
         * @brief Test if the box contains the argument box.
         *
         * @param box Box that may be contained.
         *
         * @return True if the box is contained.  False otherwise.
         */
        bool Contains(const Box3 & box);
};

}
#endif
