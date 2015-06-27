#ifndef ImpossibleGame_Systems_ImpossibleGameSystems_H_
#define ImpossibleGame_Systems_ImpossibleGameSystems_H_

#include <Ancona/Core2D/Systems/CameraSystem.hpp>
#include <Ancona/Core2D/Systems/Drawable/DrawableSystem.hpp>
#include <Ancona/Core2D/Systems/Drawable/FadeDrawableSystem.hpp>
#include <Ancona/Core2D/Systems/InputControlSystem.hpp>
#include <Ancona/Core2D/Systems/Collision/CollisionSystem.hpp>
#include <Ancona/Framework/EntityFramework/SystemManager.hpp>
#include <Ancona/Framework/Screens/ScreenManager.hpp>
#include <Ancona/Framework/Systems/ScreenSystemsContainer.hpp>
#include <Ancona/Platformer/Physics/PlatformPhysicsSystem.hpp>

#include "../Input/ImpossibleInputHandler.hpp"
#include "CounterSystem.hpp"

namespace ild
{

class ImpossibleGameSystems : public ScreenSystemsContainer
{
    public:
        ImpossibleGameSystems(ScreenManager & screenManager);


        /* getters and setters */
        DrawableSystem & drawable() { return *_drawable; }
        InputControlSystem & input() { return *_input; }
        PlatformPhysicsSystem & physics() { return *_physics; }
        CameraSystem & camera() { return *_camera; }
        CollisionSystem & collision() { return *_collision; }
        FadeDrawableSystem & fadeDrawable() { return *_fadeDrawable; }
        CounterSystem & counter() { return *_counter; }

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

        FadeDrawableSystem * _fadeDrawable;
        CounterSystem * _counter;
};


}
#endif
