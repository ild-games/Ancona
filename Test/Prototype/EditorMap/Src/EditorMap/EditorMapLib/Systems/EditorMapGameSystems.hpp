#ifndef EditorMap_Systems_EditorMapGameSystems_H_
#define EditorMap_Systems_EditorMapGameSystems_H_

#include <Ancona/Core2D/Systems/CameraSystem.hpp>
#include <Ancona/Core2D/Systems/Drawable/DrawableSystem.hpp>
#include <Ancona/Core2D/Systems/InputControlSystem.hpp>
#include <Ancona/Core2D/Systems/Collision/CollisionSystem.hpp>
#include <Ancona/Framework/EntityFramework/SystemManager.hpp>
#include <Ancona/Framework/Screens/ScreenManager.hpp>
#include <Ancona/Framework/Systems/ScreenSystemsContainer.hpp>
#include <Ancona/Platformer/Actions/ActionSystem.hpp>

namespace ild
{

/**
 * @brief Game systems used by EditorMap
 */
class EditorMapGameSystems : public ScreenSystemsContainer
{
    public:
        /**
         * @brief Constructs the game systems for EditorMap
         *
         * @param screenManager Screen Manager for the game.
         */
        EditorMapGameSystems(ScreenManager & screenManager);

        /* getters and setters */
        DrawableSystem & drawable() { return *_drawable; }
        InputControlSystem & input() { return *_input; }
        PositionSystem & position() { return *_position; }
        ActionSystem & action() { return *_action; }
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
         * @brief The position system for the game
         */
        PositionSystem * _position;
        /**
         * @brief System for managing camera componenets.
         */
        CameraSystem * _camera;
        /**
         * @brief System for managing collisions.
         */
        CollisionSystem * _collision;

        /**
         * @brief System for managing complex movements of Entities.
         */
        ActionSystem * _action;

};

}

#endif
