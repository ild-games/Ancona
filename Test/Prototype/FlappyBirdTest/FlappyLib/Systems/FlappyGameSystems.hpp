#ifndef Test_Prototype_FlappyBirdTest_Systems_FlappyGameSystems_H_
#define Test_Prototype_FlappyBirdTest_Systems_FlappyGameSystems_H_

#include <Ancona/Framework/EntityFramework/SystemManager.hpp>
#include <Ancona/Framework/Core/Systems/PositionSystem.hpp>
#include <Ancona/Framework/Core/Systems/Drawable/DrawableSystem.hpp>
#include <Ancona/Framework/Core/Systems/Drawable/FadeDrawableSystem.hpp>
#include <Ancona/Framework/Core/Systems/InputControlSystem.hpp>
#include <Ancona/Framework/Core/Systems/SimpleGravitySystem.hpp>
#include <Ancona/Framework/Core/Systems/Collision/CollisionSystem.hpp>
#include "FlappyRotateSystem.hpp"
#include "PipeSpawnerSystem.hpp"

namespace ild
{

/**
 * @brief GameSystems is used as a factory and a container for all
 *        the systems used for gameplay.
 *
 * @author Tucker Lein
 */
class FlappyGameSystems
{
    public:
        /**
         * @brief Constructs the container for the game's systems.
         *
         * @param window RenderWindow instance for the game.
         */
        FlappyGameSystems(sf::RenderWindow & window);


        /* getters and setters */
        SystemManager & GetManager() { return *_manager; }
        PositionSystem & GetPosition() { return *_position; } 
        DrawableSystem & GetDrawable() { return *_drawable; } 
        InputControlSystem & GetInput() { return *_input; } 
        SimpleGravitySystem & GetSimpleGravity() { return *_gravity; } 
        CollisionSystem & GetCollision() { return *_collision; } 
        FlappyRotateSystem & GetFlappyRotate() { return *_flappyRotate; } 
        PipeSpawnerSystem & GetPipeSpawner() { return *_pipeSpawner; } 
        FadeDrawableSystem & GetFadeDrawable() { return *_fadeDrawable; }

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
         * @brief System for managing gravity components.
         */
        SimpleGravitySystem * _gravity;
        /**
         * @brief System for managing collision components.
         */
        CollisionSystem * _collision;
        /**
         * @brief System for managing FlappyRotate components.
         */
        FlappyRotateSystem * _flappyRotate;
        /**
         * @brief System for managing PipeSpawner components.
         */
        PipeSpawnerSystem * _pipeSpawner;
        /**
         * @brief System for managing FadeDrawable components.
         */
        FadeDrawableSystem * _fadeDrawable;
};

}

#endif
