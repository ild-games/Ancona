#ifndef Ghosted_Input_GhostedInputHandler_H_
#define Ghosted_Input_GhostedInputHandler_H_

#include <Ancona/Core2D/InputDevices/InputHandler.hpp>
#include <Ancona/Core2D/Systems/InputControlComponent.hpp>

#include "../Systems/GhostedGameSystems.hpp"

namespace ild
{

class GhostedGameSystems;
class GhostedInputComponent;

/**
 * @brief Base InputHandler for Ghosted
 */
class GhostedInputHandler : public InputHandler
{
    public:
        /**
         * @brief Registers the input component that handles the actions done via input.
         *
         * @param component InputComponent instance
         */
        void RegisterInputComponent(GhostedInputComponent * component);

        /**
         * @brief Captures input and calls out to the inputComponent's actions.
         */
        virtual void HandleInput() { };

        /* getters and setters */
        void systems(GhostedGameSystems * systems) { _systems = systems; }
    protected:
        GhostedInputComponent * _playerComponent;
        GhostedGameSystems * _systems;
};

/**
 * @brief InputComponent for game player interaction for Ghosted
 */
class GhostedInputComponent : public InputControlComponent
{
    public:
        /**
         * @brief Constructs the input component used by Ghosted
         *
         * @param player Entity that represents the player.
         * @param systems GameSystems for Ghosted
         * @param inputHandler InputHandler for Ghosted
         */
        GhostedInputComponent(
                const Entity & player,
                GhostedGameSystems & systems,
                GhostedInputHandler & inputHandler);

    private:
        Entity _playerEntity;
        GhostedGameSystems & _systems;
};

}

#endif
