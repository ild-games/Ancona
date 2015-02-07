#ifndef Ancona_Engine_Physics_PhysicsSystem_hpp
#define Ancona_Engine_Physics_PhysicsSystem_hpp

#include <memory>

#include <Ancona/Engine/Physics/BasePhysicsSystem.hpp>

#include <Ancona/Engine/Physics/Position.hpp>
#include <Ancona/Engine/Physics/Actions.hpp>

namespace ild
{

class PlatformPhysicsComponent : public BasePhysicsComponent
{
    public:
        /**
         * @brief Initialize the platform physics component with the given location.
         *
         * @param location Location to initialize the component at.
         */
        PlatformPhysicsComponent(Point location);

        /**
         * @brief Update the component.  This will apply any active actions to the physical state.
         *
         * @param delta 
         */
        void Update(float delta);

        inline Actions & GetActions() { return _actions; }
    private:
        Actions _actions;
};

class PlatformPhysicsSystem : public BasePhysicsSystem
{
    public:

        /**
         * @brief Construct and initialize the PlatformPhysicsSystem.
         *
         * @param manager System manager the physics system belongs to.
         */
        PlatformPhysicsSystem(SystemManager & manager);
        
        /**
         * @brief Update all of the components in the physics system.
         *
         * Update Process:
         * 1. Apply Actions
         * 2. Fix solid body collisions.
         * 3. Call collision handling code.
         *
         * @param delta Time passed in seconds since the last update.
         */
        void Update(float delta);

        /**
         * @brief Create a Platform Physics Component and add it to the system.
         *
         * @param entity Entity to add the component to.
         * @param location Location to start the entity at. Defaults to (0,0)
         *
         * @return A pointer to the physics component.
         */
        PlatformPhysicsComponent * CreateComponent(const Entity & entity, Point location = Point());

        /**
         * @brief Has the same behavior as the UnorderedSystem operator.
         * This method simply casts the component to PlatformPhysicsComponent.
         */
        PlatformPhysicsComponent * operator [] (const Entity & entity);

        /**
         * @brief Has the same behavior as the UnorderedSystem method.
         * This method simply casts the component to PlatformPhysicsComponent.
         */
        PlatformPhysicsComponent * at(const Entity & entity);
};

}
#endif
