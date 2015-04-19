#ifndef Ancona_Engine_Physics_Position_hpp
#define Ancona_Engine_Physics_Position_hpp

#include <SFML/System.hpp>

#include <Ancona/Framework/Loading/Loading.hpp>

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
        /**
         * @copydoc ild::CameraComponent::Serialize
         */
        void Serialize(Archive & arc);

        /* getters and setters */
        //Access the current physical state of the entity.
        inline const Point & position() const { return _position; }
        inline const Point & velocity() const { return _velocity; }
        inline void position(const Point & position) { _position = position; }
        inline void velocity(const Point & velocity) { _velocity = velocity; }
        bool onGround() const;
        void groundDirection(Point groundDirection) { _groundDirection = groundDirection; }
        const Point & groundDirection() const { return _groundDirection; }
    private:
        Point _position;
        Point _velocity;
        Point _groundDirection;
};

}
#endif
