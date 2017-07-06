#ifndef Ancona_Util2D_Box2_H_
#define Ancona_Util2D_Box2_H_

#include <vector>

#include <SFML/System.hpp>

#include <Ancona/Util2D/Collision/Box3.hpp>
#include <Ancona/Util2D/Collision/Math.hpp>

namespace ild
{

/**
 * @brief Represents a square in 2d space with dimension, position,
 * and rotation
 * @author Jeff Swenson
 */
class Box2
{
    public:
        /**
         * @brief Position of the box.  The position is located at the center.
         */
        sf::Vector2f Position;
        /**
         * @brief Dimension of the box:  Length X Width
         */
        sf::Vector2f Dimension;
        /**
         * @brief Anchor point to rotate the box around
         */
        sf::Vector2f Anchor;
        /**
         * @brief The rotation of the box.
         */
        float Rotation;

        /**
         * @brief Create a square
         *
         * @param position Position of the square.  The position is in the center of the square.
         * @param dimension Dimension of the square
         * @param rotation Rotation of the square
         */
        Box2(const sf::Vector2f & position = sf::Vector2f(),
             const sf::Vector2f & dimension = sf::Vector2f(),
             const sf::Vector2f & anchor = sf::Vector2f(),
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
         * @param dimX Size in the X dimension.
         * @param dimY Size in the Y dimension.
         */
        Box2(float dimX, float dimY);

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
         * @param fixNormal Direction that of the fix that will push this box out of the argument box.
         * @param fixMagnitude Magnitude of the fix.
         *
         * @return True if they intersect.  False otherwise.
         */
        bool Intersects(const Box2 & box, sf::Vector2f & fixNormal, float & fixMagnitude) const;

        /**
         * @brief Get the normal to the edge that is colliding with or
         * adjacent to the argument box.
         *
         * @param box Box to find the nearest edge to.
         *
         * @return Normal from the nearest edge.
         */
        sf::Vector2f GetNormalOfCollisionEdge(const Box2 & box) const;

        /**
         * Determine if the box contains the point.
         * @param  point check for contains.
         * @return True if the point is in in the box.
         */
        bool ContainsPoint(const sf::Vector2f & point);

        /**
         * @brief Clear the vertices vector and fill it with vertices for the box.
         *
         * @param vertices A vector used as an output parameter for the vertices.
         */
        void GetVertices(std::vector< std::pair<float,float> > & vertices) const;

        std::pair<float, float> BotRight() const {
            return Math::RotatePoint(
                std::pair<float, float>(Position.x + Dimension.x, Position.y + Dimension.y),
                std::pair<float, float>(Position.x + (Dimension.x * Anchor.x), Position.y + (Dimension.y * Anchor.y)),
                Rotation);
        }

        std::pair<float, float> BotLeft() const {
            return Math::RotatePoint(
                std::pair<float, float>(Position.x, Position.y + Dimension.y),
                std::pair<float, float>(Position.x + (Dimension.x * Anchor.x), Position.y + (Dimension.y * Anchor.y)),
                Rotation);
        }

        std::pair<float, float> TopLeft() const {
            return Math::RotatePoint(
                std::pair<float, float>(Position.x, Position.y),
                std::pair<float, float>(Position.x + (Dimension.x * Anchor.x), Position.y + (Dimension.y * Anchor.y)),
                Rotation);
        }

        std::pair<float, float> TopRight() const {
            return Math::RotatePoint(
                std::pair<float, float>(Position.x + Dimension.x, Position.y),
                std::pair<float, float>(Position.x + (Dimension.x * Anchor.x), Position.y + (Dimension.y * Anchor.y)),
                Rotation);
        }

        /* getters and setters */
        void position(float x, float y);
        void dimension(float x, float y) {Dimension.x = x; Dimension.y = y;};
    private:
        bool SATCollision(const Box2 & box, sf::Vector2f & fixNormal, float & fixMagnitude) const;
};

}
#endif
