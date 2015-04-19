#ifndef Ancona_Game_Screens_FlappyScreen_H_
#define Ancona_Game_Screens_FlappyScreen_H_

#include <map>

#include <Ancona/Framework/Screens/AbstractScreen.hpp>
#include <Ancona/Framework/EntityFramework/Entity.hpp>
#include <Ancona/Framework/Core/Systems/Collision/CollisionSystem.hpp>
#include "../Systems/FlappyGameSystems.hpp"

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
         * @param showIntro True if the intro section is supposed to happen, otherwise false.
         *        Defaults to true.
         */
        FlappyScreen(
                ScreenManager & manager, 
                FlappyInputHandler * inputHandler,
                bool showIntro = true);

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
        void Draw(float delta);

        void RestartGame();
    private:
        /**
         * @brief InputHandler used by the screen.
         */
        FlappyInputHandler * _inputHandler;

        /**
         * @brief Container for all systems.
         */
        FlappyGameSystems * _systems;
        /**
         * @brief Holds references to entities that need to be access
         */
        std::map<std::string, Entity> _entities;
        /**
         * @brief Map containing all the collision types for the screen.
         */
        std::map<std::string, CollisionType> _collisionTypes;
        /**
         * @brief True if the intro section is supposed to happen, otherwise false.
         */
        bool _showIntro;
};

}

#endif

