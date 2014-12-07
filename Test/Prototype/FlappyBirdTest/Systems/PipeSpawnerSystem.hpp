#ifndef Test_Prototype_FlappyBirdTest_Systems_PipeSpawnerSystem_H_
#define Test_Prototype_FlappyBirdTest_Systems_PipeSpawnerSystem_H_

#include <Ancona/Engine/EntityFramework/UnorderedSystem.hpp>
#include "PipeSpawnerComponent.hpp"
#include <Ancona/Engine/Core/Systems/SpriteSystem.hpp>
#include <Ancona/Engine/Core/Systems/PositionSystem.hpp>
#include <Ancona/Engine/EntityFramework/SystemManager.hpp>
#include <Ancona/Engine/Core/Systems/Collision/CollisionSystem.hpp>

namespace ild
{

/**
 * @brief  System for spawning the continous pipes the flappy bird must flap through.
 *
 * @author Tucker Lein
 */
class PipeSpawnerSystem : public UnorderedSystem<PipeSpawnerComponent>
{
    public:
        /**
         * @brief Construct a pipe spawner system and register it with the manager.
         *
         * @param manager Manager that the system belongs to.
         */
        PipeSpawnerSystem(SystemManager & manager);

        /**
         * @brief Calls the update on the connected components.
         *
         * @param delta Number of seconds since last update.
         */
        void Update(float delta);

        /**
         * @brief Create and attach a pipe spawner component for the entity.
         *
         * @param entity Entity that they component is attached to.
         * @param spriteSystem System to make the sprite components for the pipes
         * @param positionSystem System to set the position and velocity of the pipes
         * @param pipeColType Collision Type of the pipe.
         *
         * @return A pointer to the pipe spawner component.
         */
        PipeSpawnerComponent * CreateComponent(
                const Entity & entity,
                SpriteSystem & spriteSystem,
                PositionSystem & positionSystem,
                CollisionSystem & collisionSystem,
                SystemManager & systemManager,
                CollisionType pipeColType);
};

}



#endif
