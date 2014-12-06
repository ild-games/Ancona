#ifndef Test_Prototype_FlappyBirdTest_Systems_PipeSpawnerComponent_H_
#define Test_Prototype_FlappyBirdTest_Systems_PipeSpawnerComponent_H_

#include <Ancona/Engine/Core/Systems/SpriteSystem.hpp>
#include <Ancona/Engine/Core/Systems/PositionSystem.hpp>
#include <Ancona/Engine/EntityFramework/SystemManager.hpp>

#include <SFML/System.hpp>

namespace ild
{

/**
 * @brief Spawns new pipes for the flappy bird to dodge and despawns old pipes
 *
 * @author Tucker Lein
 */
class PipeSpawnerComponent
{
    public:
        /**
         * @brief Create a pipe spawner component
         *
         * @param ...
         */
        PipeSpawnerComponent(
                SpriteSystem & spriteSystem,
                PositionSystem & positionSystem,
                SystemManager & systemManager);

        /**
         * @brief Determines if to spawn a new set of pipes, or despawn any older ones
         */
        void Update();

    private:
        /**
         * @brief System used to create the sprite components for the spawned pipes.
         */
        SpriteSystem & _spriteSystem;

        /**
         * @brief System used to create the position components for the spawned pipes.
         */
        PositionSystem & _positionSystem;

        /**
         * @brief System Manager used to spawn new entities.
         */
        SystemManager & _systemManager;

        /**
         * @brief Used to time out when to spawn pipes.
         */
        sf::Clock * _clock;

        /**
         * @brief Responsible for creating the next pair of pipes and adding them into the manager.
         */
        void SpawnPipePair();

};

}

#endif
