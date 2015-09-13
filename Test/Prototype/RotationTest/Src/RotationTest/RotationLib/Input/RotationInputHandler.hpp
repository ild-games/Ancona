#ifndef Rotation_Input_RotationInputHandler_H_
#define Rotation_Input_RotationInputHandler_H_

#include <Ancona/Core2D/InputDevices/InputHandler.hpp>
#include <Ancona/Core2D/Systems/InputControlComponent.hpp>

#include "../Systems/RotationGameSystems.hpp"

namespace ild
{

class RotationGameSystems;
class RotationInputComponent;

/**
 * @brief Base InputHandler for RotationTest
 */
class RotationInputHandler : public InputHandler
{
    public:
        /**
         * @brief Registers the input component that handles the actions done via input.
         *
         * @param component InputComponent instance
         */
        void RegisterInputComponent(RotationInputComponent * component);

        /**
         * @brief Captures input and calls out to the inputComponent's actions.
         */
        virtual void HandleInput() { };

        /* getters and setters */
        void systems(RotationGameSystems * systems) { _systems = systems; }
    protected:
        RotationInputComponent * _playerComponent;
        RotationGameSystems * _systems;
};

/**
 * @brief InputComponent for game player interaction for RotationTest
 */
class RotationInputComponent : public InputControlComponent
{
    public:
        /**
         * @brief Constructs the input component used by RotationTest
         *
         * @param player Entity that represents the player.
         * @param systems GameSystems for RotationTest
         * @param inputHandler InputHandler for RotationTest
         */
        RotationInputComponent(
                const Entity & player,
                RotationGameSystems & systems,
                RotationInputHandler & inputHandler);

    private:
        Entity _playerEntity;
        RotationGameSystems & _systems;
};

}

#endif
