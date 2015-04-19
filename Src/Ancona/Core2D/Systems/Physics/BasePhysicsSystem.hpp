#ifndef Ancona_Engine_Physics_BasePhysicsSystem_hpp
#define Ancona_Engine_Physics_BasePhysicsSystem_hpp

#include <Ancona/Core2D/Systems/Physics/Position.hpp>
#include <Ancona/Engine/EntityFramework/UnorderedSystem.hpp>
#include <Ancona/Engine/Loading/Loading.hpp>

namespace ild
{

class BasePhysicsComponent
{
    public:
        /**
         * @brief Overriable default destructor.
         */
        virtual ~BasePhysicsComponent() {}

        /**
         * @copydoc ild::CameraComponent::Serialize
         */
        void Serialize(Archive & arc);

        /**
         * @brief Get information about the Entities position.
         *
         * @return A constant reference to the position information.
         */
        const Position & GetInfo() const { return _position ; }

        /**
         * @brief Get a mutable copy of the entities position.  This should
         * be used with great care.  
         *
         * @return A mutable reference to the entities position.
         */
        Position & GetMutableInfo() { return _position; }

    protected:
        /**
         * @brief The position information for the component.
         */
        Position _position;
};

/**
 * @brief A Base Physics System that allows access 
 *  to information that is not closely tied to a games world.
 * @author Jeff Swenson
 */
class BasePhysicsSystem : public UnorderedSystem<BasePhysicsComponent>
{
    public:

        /* getters and setters */
        inline void gravity(Point gravity) { _gravity = gravity; }
        inline const Point & gravity() { return _gravity; }
    protected:
        /**
         * @brief Constructor of a BasePhysicsSystem and register it with the manager.  
         *
         * @param systemName Name of the system.
         * @param manager Manager that the system belongs to.
         */
        BasePhysicsSystem(
                std::string systemName,
                SystemManager & manager);


        /**
         * @brief Update the physics components.  Must be implemented by the child physics system.
         *
         * @param delta Fraction of a second since the last update.
         */
        void Update(float delta) = 0;

    private:
        Point _gravity;
};

}
#endif
