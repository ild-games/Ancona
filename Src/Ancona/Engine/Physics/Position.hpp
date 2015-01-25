#ifndef Ancona_Engine_Physics_Position_hpp
#define Ancona_Engine_Physics_Position_hpp

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
        inline const Point & GetPosition() { return _position._position; }
        inline const Point & GetVelocity() { return _position._velocity; }
        inline const Point & GetAcceleration() { return _position._acceleration; }

        inline void SetPosition(const Point & position) { _position = position; }
        inline void SetVelocity(const Point & velocity) { _velocity = velocity; }
        inline void SetAcceleration(const Point & acceleration) { _position = acceleration; }

        Point _position;
        Point _veloctiy;
        Point _acceleration;
};

#endif
