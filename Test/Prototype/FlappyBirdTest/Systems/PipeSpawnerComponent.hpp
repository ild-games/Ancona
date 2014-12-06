#ifndef Test_Prototype_FlappyBirdTest_Systems_PipeSpawnerComponent_H_
#define Test_Prototype_FlappyBirdTest_Systems_PipeSpawnerComponent_H_

#include <Ancona/Engine/Core/Systems/SpriteSystem.hpp>
#include <Ancona/Engine/Core/Systems/PositionSystem.hpp>
#include <Ancona/Engine/EntityFramework/SystemManager.hpp>
#include <Ancona/Engine/Core/Systems/Collision/CollisionSystem.hpp>

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
                CollisionSystem & collisionSystem,
                SystemManager & systemManager,
                CollisionType pipeColType);

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
         * @brief System used to create the collision components for the spawned pipes.
         */
        CollisionSystem & _collisionSystem;

        /**
         * @brief System Manager used to spawn new entities.
         */
        SystemManager & _systemManager;

        /**
         * @brief Used to time out when to spawn pipes.
         */
        sf::Clock * _clock;

        /**
         * @brief Stores all the spawned pipes, used to track and remove them when necessary.
         */
        std::vector<Entity> _currentPipes;

        /**
         * @brief Collision type associated with the pipes.
         */
        CollisionType _pipeColType;

        /**
         * @brief Number of seconds in between each spawn.
         */
        float const SECONDS_BETWEEN_SPAWN = 1.75f;

        /**
         * @brief Height of the gap inbetween a spawned pair of pipes.
         */
        float const GAP_HEIGHT = 40;

        /**
         * @brief Speed the pipe moves at.
         */
        float const PIPE_SPEED = -65.0f;

        /**
         * @brief Minimum y coordinate the bottom pipe can spawn at.
         */
        int const MIN_Y_BOTTOM_PIPE = 175;

        /**
         * @brief Maximum y coordinate the bottom pipe can spawn at.
         */
        int const MAX_Y_BOTTOM_PIPE = 260;

        /**
         * @brief Random number engine for location spawning of the y coordinate.
         */
        std::mt19937 _mtEngine;

        /**
         * @brief Random number distribution for location spawning of the y coordinate.
         */
        std::uniform_int_distribution<int> _randDistribution;

        /**
         * @brief Responsible for creating the next pair of pipes and adding them into the manager.
         */
        void SpawnPipePair();

        /**
         * @brief Responsible for deleting the pair of pipes on front of the _currentPipes vector.
         */
        void DespawnPipePair();

        /**
         * @brief Determines if it is time to spawn another set of pipes.
         *
         * @return True if another pair of pipes should be spawned, otherwise false.
         */
        bool TimeToSpawn();

        /**
         * @brief Determines if it is time to despawn a set of pipes that the player has already passed.
         *
         * @return True if a pair of pipes at the front of the _currentPipes vector should be removed. 
         */
        bool TimeToDespawn();

        /**
         * @brief Constructs the pipes with the correct initial values.
         *
         * @param x The x coordinate of the pipe.
         * @param y The y coordinate of the pipe.
         * @param topPipe True if the pipe is the top pipe, false if it is the bottom pipe.
         *
         * @return 
         */
        Entity CreatePipe(float x, float y, bool topPipe);

        /**
         * @brief Determiens which pipe sprite to use based on if it's the top or bottom pipe.
         *
         * @param topPipe True if the pipe is the top pipe, false for bottom pipe.
         *
         * @return The std::string that is the key for the sprite of the pipe.
         */
        std::string SpriteToUse(bool topPipe);

        /**
         * @brief Determine the y coordinate of the bottom pipe. This will be random and 
         *        the top pipe's y coordinate will be directly tied to it so the gap inbetween
         *        the pipe's is equal to GAP_HEIGHT.
         *
         * @return The y coordinate for the bottom pipe. 
         */
        float PickBottomPipeY();
};

}

#endif
