#ifndef Ancona_Game_Core_Systems_SimpleGravitySystem_H_
#define Ancona_Game_Core_Systems_SimpleGravitySystem_H_

#include <Ancona/Engine/EntityFramework/UnorderedSystem.hpp>
#include <Ancona/Engine/Core/Systems/SimpleGravityComponent.hpp>

#include <SFML/System.hpp>

namespace ild
{

/**
 * @brief System for managing SimpleGravityComponents
 *
 * @author Tucker Lein
 */
class SimpleGravitySystem : public UnorderedSystem<SimpleGravityComponent>
{
    public:
        /**
         * @brief Default constructor.
         *
         * @param manager SystemManager instance for the current screen.
         */
        SimpleGravitySystem(SystemManager & manager);

        /**
         * @brief Updates the system.
         *
         * @param delta Seconds since last update.
         */
        void Update(float delta);

        /**
         * @brief Constructs a SimpleGravityComponent using the components
         *        default constructor.
         *
         * @param entity Entity to attach the component to.
         * @param positionComponent PositionComponent of the entity.
         *
         * @return Component instance made.
         */
        SimpleGravityComponent * CreateComponent(
                const Entity & entity,
                PositionComponent & positionComponent);

        /**
         * @brief Constructs a SimpleGravityComponent with a rotation 
         *        amount specified.
         *
         * @param entity Entity to attach the component to.
         * @param positionComponent PositionComponent of the entity.
         * @param degreeRotation Amount in degrees to rotate the gravity.
         *
         * @return Component instance made.
         */
        SimpleGravityComponent * CreateComponent(
                const Entity & entity,
                PositionComponent & positionComponent,
                float degreeRotation);
};

}

#endif
