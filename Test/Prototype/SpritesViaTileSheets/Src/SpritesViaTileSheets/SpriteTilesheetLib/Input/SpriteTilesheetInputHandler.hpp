#ifndef SpriteTilesheet_Input_SpriteTilesheetInputHandler_H_
#define SpriteTilesheet_Input_SpriteTilesheetInputHandler_H_

#include <Ancona/Core2D/InputDevices/InputHandler.hpp>
#include <Ancona/Core2D/Systems/InputControlComponent.hpp>

#include "../Systems/SpriteTilesheetGameSystems.hpp"

namespace ild
{

class SpriteTilesheetGameSystems;
class SpriteTilesheetInputComponent;

/**
 * @brief Base InputHandler for SpritesViaTileSheets
 */
class SpriteTilesheetInputHandler : public InputHandler
{
    public:
        /**
         * @brief Registers the input component that handles the actions done via input.
         *
         * @param component InputComponent instance
         */
        void RegisterInputComponent(SpriteTilesheetInputComponent * component);

        /**
         * @brief Captures input and calls out to the inputComponent's actions.
         */
        virtual void HandleInput() { };

        /* getters and setters */
        void systems(SpriteTilesheetGameSystems * systems) { _systems = systems; }
    protected:
        SpriteTilesheetInputComponent * _playerComponent;
        SpriteTilesheetGameSystems * _systems;
};

/**
 * @brief InputComponent for game player interaction for SpritesViaTileSheets
 */
class SpriteTilesheetInputComponent : public InputControlComponent
{
    public:
        /**
         * @brief Constructs the input component used by SpritesViaTileSheets
         *
         * @param player Entity that represents the player.
         * @param systems GameSystems for SpritesViaTileSheets
         * @param inputHandler InputHandler for SpritesViaTileSheets
         */
        SpriteTilesheetInputComponent(
                const Entity & player,
                SpriteTilesheetGameSystems & systems,
                SpriteTilesheetInputHandler & inputHandler);

    private:
};

}

#endif
