#ifndef Ancona_Game_Systems_GameScreenSystems_H_
#define Ancona_Game_Systems_GameScreenSystems_H_

#include <SFML/Graphics.hpp>

#include <Ancona/Engine/Core/Systems/CameraSystem.hpp>
#include <Ancona/Engine/Core/Systems/Collision/CollisionSystem.hpp>
#include <Ancona/Engine/Core/Systems/Drawable/DrawableSystem.hpp>
#include <Ancona/Engine/Core/Systems/InputControlSystem.hpp>
#include <Ancona/Engine/Core/Systems/ScreenSystemsContainer.hpp>
#include <Ancona/Engine/EntityFramework/SystemManager.hpp>
#include <Ancona/Engine/Screens/ScreenManager.hpp>
#include <Ancona/Platformer/Physics/PlatformPhysicsSystem.hpp>

namespace ild
{

/**
 * @brief GameScreenSystems is used as a factory and a container for all 
 *        the systems used for gameplay.
 *
 * @author Jeff Swenson
 * @author Tucker Lein
 */
class GameScreenSystems : public ScreenSystemsContainer
{
    public:
        /**
         * @brief Constructs the container for the game's systems.
         *
         * @param screenManager ScreenManager for the game screen.
         */
        GameScreenSystems(
                ScreenManager & screenManager,
                int profile);

        /* getters and setters */
        PlatformPhysicsSystem & physics() { return *_physics; }
        DrawableSystem & drawable() { return *_drawable; }
        InputControlSystem & input() { return *_input; }
        CollisionSystem & collision() { return *_collision; }
        CameraSystem & camera() { return *_camera; }

    private:
        /**
         * @brief System for managing an entity's position
         */
        PlatformPhysicsSystem * _physics;
        /**
         * @brief System for managing an entity's sprites
         */
        DrawableSystem * _drawable;
        /**
         * @brief System for managing an entity's input
         */
        InputControlSystem * _input; 
        /**
         * @brief System for managing collision components.
         */
        CollisionSystem * _collision;
        /**
         * @brief System for managing camera componenets.
         */
        CameraSystem * _camera;
};

}
#endif
