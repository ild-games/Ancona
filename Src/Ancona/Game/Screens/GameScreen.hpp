#ifndef Ancona_Game_Screens_GameScreen_H_
#define Ancona_Game_Screens_GameScreen_H_

#include <map>

#include <Ancona/Engine/Core/Systems/Collision/CollisionSystem.hpp>
#include <Ancona/Engine/Core/Systems/InputControlSystem.hpp>
#include <Ancona/Engine/Core/Systems/SimpleGravitySystem.hpp>
#include <Ancona/Engine/Core/Systems/PositionSystem.hpp>
#include <Ancona/Engine/Core/Systems/SpriteSystem.hpp>
#include <Ancona/Engine/EntityFramework/Entity.hpp>
#include <Ancona/Engine/EntityFramework/SystemManager.hpp>
#include <Ancona/Engine/Screens/AbstractScreen.hpp>
#include <Ancona/Game/Systems/GameSystems.hpp>

namespace ild
{

/**
 * @brief Screen used for core gameplay
 *
 * @author Tucker Lein
 */
class GameScreen : public AbstractScreen
{
    public:
        /**
         * @brief Default constructor for screen.
         *
         * @param manager ScreenManager instance for the game.
         */
        GameScreen(ScreenManager & manager);

        /**
         * @brief Updates the entity systems on the screen 
         *
         * @param delta seconds since last update
         */
        void Update(float delta);

        /**
         * @brief Initialization logic for GameScreen, safe place
         *        to access resources brought in by the resource
         *        loader.
         */
        void Init();

        /**
         * @brief Draws the systems on the screen
         */
        void Draw();
    private:
        /**
         * @brief Container for all systems.
         */
        GameSystems * _systems;

        /**
         * @brief Entity for the player
         */
        Entity _player;

        /**
         * @brief Entity for the ground
         */
        Entity _ground;

        /**
         * @brief Map containing all the collision types for the screen.
         */
        std::map<std::string, CollisionType> _collisionTypes;
};

}

#endif
