#ifndef Ancona_Engine_Core_Systems_PositionSystem_H_
#define Ancona_Engine_Core_Systems_PositionSystem_H_

#include <SFML/System.hpp>

#include <Ancona/Engine/EntityFramework/UnorderedSystem.hpp>
#include "PositionComponent.hpp"

namespace ild
{

/**
 * @brief The position system allows entities to have a position and a velocity
 *
 * @author Jeff Swenson
 */
class PositionSystem : public UnorderedSystem<PositionComponent>
{
    public:
        /**
         * @brief Construct a position system and register it with the manager.
         *
         * @param manager Manager that the system belongs to.
         */
        PositionSystem(SystemManager & manager);

        /**
         * @brief Update the position for all components based off of their velocity
         *
         * @param delta Number of seconds since last update
         */
        void Update(float delta);

        /**
         * @brief Create and attach a position component for the entity.
         *
         * @param entity Entity that the component is attached to
         * @param initialPosition Initial position of the entity.
         * @param initialVelocity Initial velocity of the entity.
         *
         * @return  A pointer to the position component.
         */
        PositionComponent * CreateComponent(const Entity & entity, 
                const sf::Vector3f & initialPosition = sf::Vector3f(),
                const sf::Vector3f & initialVelocity = sf::Vector3f());
};

}
#endif
