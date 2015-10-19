#ifndef EditorMap_Input_EditorMapInputHandler_H_
#define EditorMap_Input_EditorMapInputHandler_H_

#include <Ancona/Core2D/InputDevices/InputHandler.hpp>
#include <Ancona/Core2D/Systems/InputControlComponent.hpp>

#include "../Systems/EditorMapGameSystems.hpp"

namespace ild
{

class EditorMapGameSystems;
class EditorMapInputComponent;

/**
 * @brief Base InputHandler for EditorMap
 */
class EditorMapInputHandler : public InputHandler
{
    public:
        /**
         * @brief Registers the input component that handles the actions done via input.
         *
         * @param component InputComponent instance
         */
        void RegisterInputComponent(EditorMapInputComponent * component);

        /**
         * @brief Captures input and calls out to the inputComponent's actions.
         */
        virtual void HandleInput() { };

        /* getters and setters */
        void systems(EditorMapGameSystems * systems) { _systems = systems; }
    protected:
        EditorMapInputComponent * _playerComponent;
        EditorMapGameSystems * _systems;
};

/**
 * @brief InputComponent for game player interaction for EditorMap
 */
class EditorMapInputComponent : public InputControlComponent
{
    public:
        /**
         * @brief Constructs the input component used by EditorMap
         *
         * @param player Entity that represents the player.
         * @param systems GameSystems for EditorMap
         * @param inputHandler InputHandler for EditorMap
         */
        EditorMapInputComponent(
                const Entity & player,
                EditorMapGameSystems & systems,
                EditorMapInputHandler & inputHandler);

    private:
        Entity _playerEntity;
        EditorMapGameSystems & _systems;
};

}

#endif
