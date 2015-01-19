#ifndef Test_Prototype_FlappyBirdTest_Systems_FlappyRotateSystem_H_
#define Test_Prototype_FlappyBirdTest_Systems_FlappyRotateSystem_H_

#include <Ancona/Engine/EntityFramework/UnorderedSystem.hpp>
#include "FlappyRotateComponent.hpp"

namespace ild 
{

/**
 * @brief  System for rotating the flappy bird appropriately
 *
 * @author Tucker Lein
 */
class FlappyRotateSystem : public UnorderedSystem<FlappyRotateComponent>
{
    public:
        /**
         * @brief Construct a flappy rotate system and register it with the manager.
         *
         * @param manager Manager that the system belongs to.
         */
        FlappyRotateSystem(SystemManager & manager);

        /**
         * @brief Update the rotation of the flappy bird based on its current trajectory
         *
         * @param delta number of seconds since last update
         */
        void Update(float delta);

        /**
         * @brief Create and attach a flappy rotate component for the entity.
         *
         * @param entity Entity that the component is attached to.
         * @param spriteComponent SpriteComponent of the flappy bird.
         * @param positionComponent PositionComponent of the flappy bird.
         *
         * @return A pointer to the flappy rotate component.
         */
        FlappyRotateComponent * CreateComponent(
                const Entity & entity,
                SpriteComponent & spriteComponent,
                PositionComponent & positionComponent);
};

}

#endif
