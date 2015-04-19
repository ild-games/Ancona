#ifndef Test_Prototype_FlappyBirdTest_Systems_PipeSpawnerSystem_H_
#define Test_Prototype_FlappyBirdTest_Systems_PipeSpawnerSystem_H_

#include <Ancona/Framework/EntityFramework/UnorderedSystem.hpp>
#include "PipeSpawnerComponent.hpp"
#include <Ancona/Framework/Core/Systems/Drawable/DrawableSystem.hpp>
#include <Ancona/Framework/Core/Systems/PositionSystem.hpp>
#include <Ancona/Framework/EntityFramework/SystemManager.hpp>
#include <Ancona/Framework/Core/Systems/Collision/CollisionSystem.hpp>

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
         * @param entity Entity that the component is attached to.
         * @param drawableSystem System to make the drawable components for the pipes
         * @param positionSystem System to set the position and velocity of the pipes
         * @param pipeColType Collision Type of the pipe.
         *
         * @return A pointer to the pipe spawner component.
         */
        PipeSpawnerComponent * CreateComponent(
                const Entity & entity,
                DrawableSystem & DrawableSystem,
                PositionSystem & positionSystem,
                CollisionSystem & collisionSystem,
                SystemManager & systemManager,
                CollisionType pipeColType,
                CollisionType pointColType);
};

}



#endif
