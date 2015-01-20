#ifndef Ancona_Game_Screens_FlappyScreen_H_
#define Ancona_Game_Screens_FlappyScreen_H_

#include <map>

#include <Ancona/Engine/Screens/AbstractScreen.hpp>
#include <Ancona/Engine/EntityFramework/Entity.hpp>
#include <Ancona/Engine/Core/Systems/Collision/CollisionSystem.hpp>
#include "../Systems/GameSystems.hpp"

namespace ild
{

class FlappyRotateSystem;
class PipeSpawnerSystem;
class CollisionSystem;
class PipeSpawnerComponent;
class FlappyInputHandler;

/**
 * @brief Screen used for core gameplay for FlappyBird
 *
 * @author Tucker Lein
 */
class FlappyScreen : public AbstractScreen
{
    public:
        /**
         * @brief Default constructor for screen.
         *
         * @param manager ScreenManager instance for the game.
         * @param inputHandler InputHandler for the game.
         */
        FlappyScreen(ScreenManager & manager, FlappyInputHandler * inputHandler);

        /**
         * @brief Updates the entity systems on the screen.
         *
         * @param delta
         */
        void Update(float delta);

        /**
         * @brief 
         */
        void Init();

        /**
         * @brief Draws the systems on the screen.
         */
        void Draw();

        void RestartGame();
    private:
        /**
         * @brief InputHandler used by the screen.
         */
        FlappyInputHandler * _inputHandler;

        /**
         * @brief Container for all systems.
         */
        GameSystems * _systems;
        /**
         * @brief Holds references to entities that need to be access
         */
        std::map<std::string, Entity> _entities;
        /**
         * @brief Map containing all the collision types for the screen.
         */
        std::map<std::string, CollisionType> _collisionTypes;
};

}

#endif

