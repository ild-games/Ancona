#ifndef JumpyGame_Systems_JumpyGameSystems_Hpp
#define JumpyGame_Systems_JumpyGameSystems_Hpp

#include <Ancona/Engine/EntityFramework/SystemManager.hpp>
#include <Ancona/Engine/Core/Systems/CameraSystem.hpp>
#include <Ancona/Engine/Core/Systems/Drawable/DrawableSystem.hpp>
#include <Ancona/Engine/Core/Systems/Drawable/FadeDrawableSystem.hpp>
#include <Ancona/Engine/Core/Systems/InputControlSystem.hpp>
#include <Ancona/Engine/Core/Systems/Collision/CollisionSystem.hpp>
#include <Ancona/Engine/Core/Systems/Physics/PlatformPhysicsSystem.hpp>
#include "../Input/JumpyKeyboard.hpp"

namespace ild
{

class JumpyGameSystems
{
    public:
        JumpyGameSystems(sf::RenderWindow & window);


        /* getters and setters */
        SystemManager & GetManager() { return *_manager; }
        DrawableSystem & GetDrawable() { return *_drawable; } 
        InputControlSystem & GetInput() { return *_input; } 
        PlatformPhysicsSystem & GetPhysics() { return *_physics; }
        CameraSystem & GetCamera() { return *_camera; }
        CollisionSystem & GetCollision() { return *_collision; }

        CollisionType GetNullCollision() { return 0; }
    private:
        /**
         * @brief Manages all the entity systems on the screen.
         */
        SystemManager * _manager;
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
