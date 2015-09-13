#ifndef Rotation_Systems_RotationGameSystems_H_
#define Rotation_Systems_RotationGameSystems_H_

#include <Ancona/Core2D/Systems/CameraSystem.hpp>
#include <Ancona/Core2D/Systems/Drawable/DrawableSystem.hpp>
#include <Ancona/Core2D/Systems/InputControlSystem.hpp>
#include <Ancona/Core2D/Systems/Collision/CollisionSystem.hpp>
#include <Ancona/Core2D/Systems/RotateSystem.hpp>
#include <Ancona/Framework/EntityFramework/SystemManager.hpp>
#include <Ancona/Framework/Screens/ScreenManager.hpp>
#include <Ancona/Framework/Systems/ScreenSystemsContainer.hpp>
#include <Ancona/Platformer/Physics/PlatformPhysicsSystem.hpp>

namespace ild
{

/**
 * @brief Game systems used by RotationTest
 */
class RotationGameSystems : public ScreenSystemsContainer
{
    public:
        /**
         * @brief Constructs the game systems for RotationTest
         *
         * @param screenManager Screen Manager for the game.
         */
        RotationGameSystems(ScreenManager & screenManager);

        /* getters and setters */
        DrawableSystem & drawable() { return *_drawable; }
        InputControlSystem & input() { return *_input; }
        PlatformPhysicsSystem & physics() { return *_physics; }
        CameraSystem & camera() { return *_camera; }
        CollisionSystem & collision() { return *_collision; }
        RotateSystem & rotate() { return *_rotate; }
        CollisionType nullCollision() { return 0; }
    private:
        /**
         * @brief System for managing an entity's drawables.
         */
        DrawableSystem * _drawable;
        /**
         * @brief System for managing an entity's input.
         */
        InputControlSystem * _input; 
        /**
         * @brief The physics system for the game
         */
        PlatformPhysicsSystem * _physics;
        /**
         * @brief System for managing camera componenets.
         */
        CameraSystem * _camera;
        /**
         * @brief System for managing collisions.
         */
        CollisionSystem * _collision;
        /**
         * @brief System for rotating drawables.
         */
        RotateSystem * _rotate;
};

}

#endif
