#ifndef Ancona_Game_Systems_GameSystems_H_
#define Ancona_Game_Systems_GameSystems_H_

#include <SFML/Graphics.hpp>

#include <Ancona/Engine/EntityFramework/SystemManager.hpp>
#include <Ancona/Engine/Core/Systems/Physics/PlatformPhysicsSystem.hpp>
#include <Ancona/Engine/Core/Systems/Drawable/DrawableSystem.hpp>
#include <Ancona/Engine/Core/Systems/InputControlSystem.hpp>
#include <Ancona/Engine/Core/Systems/Collision/CollisionSystem.hpp>

namespace ild
{

/**
 * @brief GameSystems is used as a factory and a container for all 
 *        the systems used for gameplay.
 *
 * @author Jeff Swenson
 */
class GameSystems
{
    public:
        /**
         * @brief Constructs the container for the game's systems.
         *
         * @param window RenderWindow instance for the game.
         */
        GameSystems(sf::RenderWindow & window);


        /* getters and setters */
        SystemManager & GetManager() { return *_manager; }
        PlatformPhysicsSystem & GetPhysics() { return *_physics; } 
        DrawableSystem & GetDrawable() { return *_drawable; } 
        InputControlSystem & GetInput() { return *_input; } 
        CollisionSystem & GetCollision() { return *_collision; } 

    private:
        /**
         * @brief Manages all the entity systems on the screen.
         */
        SystemManager * _manager;
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
};

}
#endif
