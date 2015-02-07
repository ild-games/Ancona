#ifndef Ancona_Engine_Physics_Position_hpp
#define Ancona_Engine_Physics_Position_hpp

#include <SFML/System.hpp>

namespace ild
{

typedef sf::Vector2f Point;

/**
 * @brief The position class is used to track state about an entities position, velocity, and acceleration.  It should not
 * be used outside of the physics system.
 * @author Jeff Swenson
 */
class Position
{
    public:
        //Access the current physical state of the entity.
        inline const Point & GetPosition() { return _position; }
        inline const Point & GetVelocity() { return _velocity; }

        inline void SetPosition(const Point & position) { _position = position; }
        inline void SetVelocity(const Point & velocity) { _velocity = velocity; }

    private:
        Point _position;
        Point _velocity;
};

}
#endif
