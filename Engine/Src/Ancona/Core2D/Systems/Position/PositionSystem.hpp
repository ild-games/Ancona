#ifndef Ancona_Engine_Position_PositionSystem_hpp
#define Ancona_Engine_Position_PositionSystem_hpp

#include <Ancona/Framework/EntityFramework/UnorderedSystem.hpp>
#include <Ancona/Framework/Serializing/Serializing.hpp>
namespace ild
{

typedef sf::Vector2f Point;

/**
 * @brief Operator used to output a Point to an out stream. The Point will be formatted as (x,y)
 */
std::ostream & operator << (std::ostream& os, const Point&pt);

class PositionComponent
{
    public:
        /**
         * @brief Overriable default destructor.
         */
        ~PositionComponent() {}

        /**
         * @copydoc ild::CameraComponent::Serialize
         */
        void Serialize(Archive & arc);

        /**
         * @copydoc ild::CameraComponent::FetchDependencies
         */
        void FetchDependencies(const Entity & entity);

        void Update(float delta);

        /* getters and setters */
        //Access the current physical state of the entity.
        inline const Point & position() const { return _position; }
        inline const Point & velocity() const { return _velocity; }
        inline void position(const Point & position) { _position = position; }
        inline void velocity(const Point & velocity) { _velocity = velocity; }

        bool onGround() const;
        void groundDirection(Point groundDirection) { _groundDirection = groundDirection; }
        const Point & groundDirection() const { return _groundDirection; }

    protected:
        Point _actualPosition;
        Point _position;
        Point _velocity;
        Point _groundDirection;

        void RoundPosition();
};

/**
 * @brief A Base Position System that allows access
 *  to information that is not closely tied to a games world.
 * @author Jeff Swenson
 */
class PositionSystem : public UnorderedSystem<PositionComponent>
{
    public:

        /* getters and setters */
        inline void gravity(Point gravity) { _gravity = gravity; }
        inline const Point & gravity() { return _gravity; }

        /**
         * @brief Constructor of a PositionSystem and register it with the manager.
         *
         * @param systemName Name of the system.
         * @param manager Manager that the system belongs to.
         */
        PositionSystem(
                std::string systemName,
                SystemManager & manager);


        /**
         * Create a position component at (0,0)
         * @param Entity entity to create the component for.
         */
        PositionComponent * CreateComponent(const Entity & entity);

    protected:
        /**
         * @brief Update the position components.  Must be implemented by the child position system.
         *
         * @param delta Fraction of a second since the last update.
         */
        void Update(float delta);

    private:
        Point _gravity;
};

}
#endif
