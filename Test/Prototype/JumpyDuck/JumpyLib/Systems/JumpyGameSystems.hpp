#ifndef JumpyGame_Systems_JumpyGameSystems_Hpp
#define JumpyGame_Systems_JumpyGameSystems_Hpp

#include <Ancona/Engine/EntityFramework/SystemManager.hpp>
#include <Ancona/Engine/Core/Systems/CameraSystem.hpp>
#include <Ancona/Engine/Core/Systems/Drawable/DrawableSystem.hpp>
#include <Ancona/Engine/Core/Systems/Drawable/FadeDrawableSystem.hpp>
#include <Ancona/Engine/Core/Systems/InputControlSystem.hpp>
#include <Ancona/Engine/Core/Systems/Collision/CollisionSystem.hpp>
#include <Ancona/Engine/Core/Systems/ScreenSystemsContainer.hpp>
#include <Ancona/Engine/Screens/ScreenManager.hpp>
#include <Ancona/Platformer/Physics/PlatformPhysicsSystem.hpp>

#include "../Input/JumpyKeyboard.hpp"

namespace ild
{

class JumpyGameSystems : public ScreenSystemsContainer
{
    public:
        JumpyGameSystems(ScreenManager & screenManager);


        /* getters and setters */
        DrawableSystem & drawable() { return *_drawable; }
        InputControlSystem & input() { return *_input; }
        PlatformPhysicsSystem & physics() { return *_physics; }
        CameraSystem & camera() { return *_camera; }
        CollisionSystem & collision() { return *_collision; }

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
};


}
#endif
