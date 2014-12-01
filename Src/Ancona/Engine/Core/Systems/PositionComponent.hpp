#ifndef Ancona_Engine_Core_Systems_PositionComponent_H_
#define Ancona_Engine_Core_Systems_PositionComponent_H_

#include <SFML/System.hpp>

namespace ild
{

/**
 * @brief  Defines position and velocity for an Entity 
 *
 * @author Jeff Swenson
 */
class PositionComponent
{
    public:
        /**
         * @brief Create a component at the given position with 
         *        the given velocity.
         *
         * @param position initial position
         * @param velocity initial velocity
         */
        PositionComponent(
                const sf::Vector3f & position, 
                const sf::Vector3f & velocity);

        /**
         * @brief Defines coordinates for the component
         */
        sf::Vector3f Position;

        /**
         * @brief Defines velocity in x, y, and z axes
         */
        sf::Vector3f Velocity;

        /**
         * @brief Updates the position based off the velocity
         */
        void Update(float delta);
};

}
#endif
