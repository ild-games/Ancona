#ifndef Ancona_Game_InputDevices_FlappyKeyboard_H_
#define Ancona_Game_InputDevices_FlappyKeyboard_H_

#include <Ancona/Engine/InputDevices/InputHandler.hpp>
#include <Ancona/Util/StateMachine/SharedMachine.hpp>
#include "../States/FlappyStates.hpp"
#include <Ancona/Engine/Screen/ScreenManager.hpp>
#include "../Screen/TestScreen.hpp"
#include <vector>

namespace ild
{

class FlappyInputComponent;

/**
 * @brief Defines the input handling for the keyboard in FlappyBird. 
 *
 * @author Tucker Lein
 */
class FlappyKeyboard : public InputHandler
{
    public:
        FlappyKeyboard(ScreenManager & screenManager);

        /**
         * @brief Handles the input for the InputHandler. Since this input handler
         *        is run off of a state machine is delegates the work to the machine
         *        here so it can call the correct input handling function depending
         *        on the current state.
         */
        void HandleInput();

        /**
         * @brief Defines how the input should be handled when the current state
         *        is FlappyStates::InAir.
         */
        void InAirInput(MachineState & curState);

        /**
         * @brief Defines how the input should be handled when the current state
         *        is FlappyStates::OnGround.
         */
        void OnGroundInput(MachineState & curState);

        /**
         * @brief Registers the FlappyInputComponent with the InputHandler
         *
         * @param component
         */
        void RegisterInputComponent(
                FlappyInputComponent * component);

        /**
         * @brief First checks if the transition from the current state to the 
         *        proposed new state is legal and then changes the state.
         *
         * @param newState Proposed new state for the state machine.
         */
        void ChangeState(const MachineState & newState);

    private:
        /**
         * @brief InputComponent that defines behavior for this input handler.
         */
        FlappyInputComponent * _component;

        /**
         * @brief StateMachine that controls which input handling functions
         *        are called.
         */
        SharedMachine<FlappyKeyboard, void> _machine;

        /**
         * @brief Current MachineState the state machine is in.
         */
        MachineState _curState;

        /**
         * @brief Used to change the screen when you restart the game.
         */
        ScreenManager & _screenManager;

        /**
         * @brief Check if the transition from the current state to the proposed new state
         *        is allowed.
         *
         * @param newState The new MachineState that the machine is told to move to.
         *
         * @return true if the transition is allowed, otherwise false.
         */
        bool AllowedTransition(const MachineState & newState);

        /**
         * @brief Checks the allowed states that can be transitioned to if the current
         *        state is FlappyStates::InAir
         *
         * @param newState The new MachineState that the machine is told to move to.
         *
         * @return true if the transition is allowed, otherwise false;
         */
        bool InAirTransitionCheck(const MachineState & newState);
};

}

#endif
