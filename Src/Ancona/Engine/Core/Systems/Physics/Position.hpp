#ifndef Ancona_Engine_Physics_Position_hpp
#define Ancona_Engine_Physics_Position_hpp

#include <SFML/System.hpp>

#include <iostream>

namespace ild
{

typedef sf::Vector2f Point;

/**
 * @brief Operator used to output a Point to an out stream. The Point will be formatted as (x,y)
 */
std::ostream & operator << (std::ostream& os, const Point&pt);

/**
 * @brief The position class is used to track state about an entities position, velocity, and acceleration.  It should not
 * be used outside of the physics system.
 * @author Jeff Swenson
 */
class Position
{
    public:
        //Access the current physical state of the entity.
        inline const Point & GetPosition() const { return _position; }
        inline const Point & GetVelocity() const { return _velocity; }

        inline void SetPosition(const Point & position) { _position = position; }
        inline void SetVelocity(const Point & velocity) { _velocity = velocity; }

        /**
         * @brief Determine if the object is on the ground.  
         *
         * @return True if it is on the ground.  False otherwise.
         */
        bool IsOnGround() const;

        /**
         * @brief Set the ground direction of the entity.
         *
         * @param groundDirection A normalized vector that points right along the ground.
         */
        void SetGroundDirection(Point groundDirection) { _groundDirection = groundDirection; }

        /**
         * @brief Get a vector that points to the right along the ground. The direction is only valid
         * when the entity is on the ground.
         *
         * @return A normalzied vector that points right along the ground.
         */
        const Point & GetGroundDirection() const { return _groundDirection; }
    private:
        Point _position;
        Point _velocity;
        Point _groundDirection;
};

}
#endif
