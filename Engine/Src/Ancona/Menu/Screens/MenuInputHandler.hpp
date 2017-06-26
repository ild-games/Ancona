#ifndef Anona_Menu_Input_MenuInputHandler_H_
#define Anona_Menu_Input_MenuInputHandler_H_

#include <Ancona/Core2D/InputDevices/InputHandler.hpp>
#include <Ancona/Core2D/Systems/InputControlComponent.hpp>

#include "MenuGameSystems.hpp"
#include "../Systems/ButtonSystem.hpp"

namespace ildmenu
{

class MenuGameSystems;
class MenuInputComponent;

/**
 * @brief InputHandler for the menu screen.
 */
class MenuInputHandler : public ild::InputHandler
{
    public:
        /**
         * @brief Registers the input component that handles the actions done via input.
         *
         * @param component InputComponent instance
         */
        void RegisterInputComponent(MenuInputComponent * component);

        /**
         * @brief Captures input and calls out to the inputComponent's actions.
         */
        virtual void HandleInput(float delta) override { };

        /* getters and setters */
        void systems(MenuGameSystems * systems) { _systems = systems; }
    protected:
        MenuInputComponent * _playerComponent;
        MenuGameSystems * _systems;
};

/**
 * @brief InputComponent for the menu screen.
 */
class MenuInputComponent : public ild::InputControlComponent
{
    public:
        /**
         * @brief Constructs the input component used by the menu screen.
         *
         * @param systems GameSystems for menu.
         * @param inputHandler InputHandler for menu.
         */
        MenuInputComponent(
                MenuGameSystems & systems,
                std::shared_ptr<MenuInputHandler> inputHandler);

        /**
         * Called by the input handlers to update the button system state.
         * @param location Location of the pointer.
         * @param isDown Is the pointer down or up.
         */
        void UpdatePointer(ild::Point location, bool isDown);

    private:
        MenuGameSystems & _systems;
};

}

#endif
