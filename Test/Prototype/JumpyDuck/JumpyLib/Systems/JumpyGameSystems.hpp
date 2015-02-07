#ifndef JumpyGame_Systems_JumpyGameSystems_Hpp
#define JumpyGame_Systems_JumpyGameSystems_Hpp

#include <Ancona/Engine/EntityFramework/SystemManager.hpp>
#include <Ancona/Engine/Core/Systems/PositionSystem.hpp>
#include <Ancona/Engine/Core/Systems/Drawable/DrawableSystem.hpp>
#include <Ancona/Engine/Core/Systems/Drawable/FadeDrawableSystem.hpp>
#include <Ancona/Engine/Core/Systems/InputControlSystem.hpp>
#include <Ancona/Engine/Core/Systems/SimpleGravitySystem.hpp>
#include <Ancona/Engine/Core/Systems/Collision/CollisionSystem.hpp>
#include <Ancona/Engine/Physics/PlatformPhysicsSystem.hpp>
#include "../Input/JumpyKeyboard.hpp"

namespace ild
{

class JumpyGameSystems
{
    public:
        JumpyGameSystems(sf::RenderWindow & window);


        /* getters and setters */
        SystemManager & GetManager() { return *_manager; }
        PositionSystem & GetPosition() { return *_position; } 
        DrawableSystem & GetDrawable() { return *_drawable; } 
        InputControlSystem & GetInput() { return *_input; } 
        PlatformPhysicsSystem & GetPhysics() { return *_physics; }

    private:
        /**
         * @brief Manages all the entity systems on the screen.
         */
        SystemManager * _manager;
        /**
         * @brief System for managing an entity's position.
         */
        PositionSystem * _position;
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
};


}
#endif
