#ifndef Test_Prototype_FlappyBirdTest_EntityFactories_PlayerFactory_H_
#define Test_Prototype_FlappyBirdTest_EntityFactories_PlayerFactory_H_

#include <map>
#include <string>

#include "../Systems/FlappyGameSystems.hpp"
#include "../InputDevices/FlappyInputHandler.hpp"

namespace ild
{

namespace factories
{
    /**
     * @brief Creates a player with all the default components setup.
     *
     * @param gameSystems GameSystems instance for screen.
     * @param collisionTypes CollisionTypes for the screen.
     * @param entities Entities on the screen.
     * @param inputHandler InputHandler for the player.
     *
     * @return Entity that is the player.
     */
    Entity CreatePlayer(
            FlappyGameSystems * gameSystems,
            std::map<std::string, CollisionType> collisionTypes,
            std::map<std::string, Entity> entities,
            FlappyInputHandler & inputHandler);

    /**
     * @brief Sets up the default player position component.
     *
     * @param player Entity that is the player.
     * @param positionSystem PositionSystem for the screen.
     */
    void SetupPlayerPosition(
            Entity player,
            PositionSystem & positionSystem);

    /**
     * @brief Sets up the default player sprite component.
     *
     * @param player Entity that is the player.
     * @param drawableSystem DrawableSystem for the screen.
     */
    void SetupPlayerSprite(
            Entity player,
            DrawableSystem & drawableSystem); 

    /**
     * @brief Sets up the default player rotation component.
     *
     * @param player Entity that is the player.
     * @param gameSystems GameSystems instance for the screen.
     */
    void SetupPlayerRotate(
            Entity player,
            FlappyGameSystems * gameSystems);

    /**
     * @brief Sets up the default player input component.
     *
     * @param player Entity that is the player.
     * @param gameSystems GameSystems instance for the screen.
     * @param inputHandler InputHandler for the player.
     */
    void SetupPlayerInput(
            Entity player,
            FlappyGameSystems * gameSystems,
            FlappyInputHandler & inputHandler);

    /**
     * @brief Sets up the default player gravity component.
     *
     * @param player Entity that is the player.
     * @param gravitySystem SimpleGravitySystem for the screen.
     * @param positionSystem PositionSystem for the screen.
     */
    void SetupPlayerGravity(
            Entity player,
            SimpleGravitySystem & gravitySystem,
            PositionSystem & positionSystem);

    /**
     * @brief Sets up the collision component and handlers for the player.
     *
     * @param player Entity that is the player.
     * @param gameSystems GameSystems instance for the screen.
     * @param collisionTypes CollisionTypes for the screen.
     * @param entities Entities on the screen.
     * @param inputHandler InputHandler for the player.
     */
    void SetupPlayerCollisions(
            Entity player, 
            FlappyGameSystems * gameSystems,
            std::map<std::string, CollisionType> collisionTypes,
            std::map<std::string, Entity> entities,
            FlappyInputHandler & inputHandler);

    /**
     * @brief Handler function for when the player collides with the ground.
     *
     * @param gameSystems GameSystems instance for the screen.
     * @param entities Entities on the screen.
     * @param inputHandler InputHandler for the player.
     *
     * @return function to handle collision.
     */
    std::function< void(Entity player, Entity ground) > PlayerToGroundCollisionHandler(
            FlappyGameSystems * gameSystems,
            std::map<std::string, Entity> entities,
            FlappyInputHandler & inputHandler);

    /**
     * @brief Handler function for when the player collides with a pipe.
     *
     * @param gameSystems GameSystems instance for the screen.
     * @param entities Entities on the screen.
     * @param inputHandler InputHandler for the player.
     *
     * @return function to handle collision.
     */
    std::function< void(Entity player, Entity ground) > PlayerToPipeCollisionHandler(
            FlappyGameSystems * gameSystems,
            std::map<std::string, Entity> entities,
            FlappyInputHandler & inputHandler);

    /**
     * @brief Handler function for when the player collides with a point.
     *
     * @param gameSystems GameSystems instance for the screen.
     * @param entities Entities on the screen.
     *
     * @return function to handle collision.
     */
    std::function< void(Entity player, Entity ground) > PlayerToPointCollisionHandler(
            FlappyGameSystems * gameSystems,
            std::map<std::string, Entity> entities);
    
    /**
     * @brief Stops all the leftward movement on the screen. Used when
     *        the flappy bird hits a pipe or the ground.
     *
     * @param gameSystems GameSystems instance for the screen.
     * @param player Player entity.
     * @param ground Ground entity.
     * @param pipeSpawner PipeSpawner entity.
     * @param inputHandler InputHandler for the player.
     */
    void StopAllMovement(
            FlappyGameSystems * gameSystems,
            Entity player,
            Entity ground,
            Entity pipeSpawner,
            FlappyInputHandler & inputHandler);
}

}

#endif
