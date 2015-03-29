#ifndef Ancona_Game_Screens_GameScreen_H_
#define Ancona_Game_Screens_GameScreen_H_

#include <map>

#include <Ancona/Engine/Screens/AbstractScreen.hpp>
#include <Ancona/Engine/EntityFramework/Entity.hpp>
#include <Ancona/Game/Systems/GameScreenSystems.hpp>
#include <Ancona/Game/EntityFactories/EnvironmentFactory.hpp>
#include <Ancona/Game/EntityFactories/PlayerFactory.hpp>

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
         * @param profile The profile used for this screen.
         */
        GameScreen(
                ScreenManager & manager,
                int profile);

        /**
         * @brief Updates the entity systems on the screen.
         *
         * @param delta seconds since last update.
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
         *
         * @param delta Seconds since last update.
         */
        void Draw(float delta);

        /* getters and setters */
        ScreenSystemsContainer * GetSystemsContainer() override { return _gameSystems.get(); }
    private:
        /**
         * @brief Container for all systems.
         */
        std::unique_ptr<GameScreenSystems> _gameSystems;
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
