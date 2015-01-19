#ifndef Ancona_Game_Systems_SimpleGravityComponent_H_
#define Ancona_Game_Systems_SimpleGravityComponent_H_

#include <Ancona/Engine/Core/Systems/PositionSystem.hpp>

namespace ild
{

/**
 * @brief Component for simple gravitational force.
 *
 * @author Tucker Lein
 */
class SimpleGravityComponent
{
    public:
        /**
         * @brief Constructs a new gravity component.
         *
         * @param positionComponent Used to manipulate the velocity of the entity.
         */
        SimpleGravityComponent(PositionComponent & positionComponent);

        /**
         * @brief Constructs a new gravity component with custom rotation.
         *
         * @param positionComponent Used to manipulate the velocity of the entity.
         * @param rotationDegrees Amount in degrees the gravity should be rotated.
         */
        SimpleGravityComponent(
                PositionComponent & positionComponent,
                float rotationDegrees);

        /**
         * @brief Updates the velocity of the entity by the force
         *        of gravity.
         *
         * @param delta Seconds since last update.
         */
        void Update(float delta);

    private:
        /**
         * @brief Force of gravity.
         */
        const float GRAVITY_F = 270.0f;

        /**
         * @brief Rotation of gravity, defaults to 0.
         */
        const float ROTATION_D;

        /**
         * @brief Used to manipulate the entity's velocity.
         */
        PositionComponent & _positionComponent;
};

}

#endif
