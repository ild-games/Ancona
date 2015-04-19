#ifndef Test_Prototype_FlappyBirdTest_InputDevices_FlappyInputHandler_H_
#define Test_Prototype_FlappyBirdTest_InputDevices_FlappyInputHandler_H_

#include <Ancona/Framework/Screens/ScreenManager.hpp>
#include <Ancona/Framework/InputDevices/InputHandler.hpp>
#include <Ancona/Util/StateMachine/SharedMachine.hpp>
#include "../States/FlappyStates.hpp"
#include "../Systems/FlappyGameSystems.hpp"


#include <SFML/Window.hpp>

namespace ild
{

class FlappyInputComponent;

/**
 * @brief InputHandler for flappy bird.
 *
 * @author Tucker Lein
 */
class FlappyInputHandler : public InputHandler
{
    public:
        /**
         * @brief Construct a FlappyInputHandler
         *
         * @param screenManager ScreenManager for the game.
         * @param initialState Optional state to start the StateMachine in, defaults to FlappyStates::GameIntro
         */
        FlappyInputHandler(
                ScreenManager & screenManager,
                MachineState initialState = FlappyStates::GameIntro);

        /**
         * @brief Handles the input for the InputHandler. Since this input handler
         *        is run off of a state machine is delegates the work to the machine
         *        here so it can call the correct input handling function depending
         *        on the current state.
         */
        void HandleInput();

        /**
         * @brief Registers the FlappyInputComponent with the InputHandler
         *
         * @param component
         */
        void RegisterInputComponent(FlappyInputComponent * component);

        /**
         * @brief First checks if the transition from the current state to the 
         *        proposed new state is legal and then changes the state.
         *
         * @param newState Proposed new state for the state machine.
         */
        void ChangeState(const MachineState & newState);

        /* getters and setters */
        void SetGameSystems(FlappyGameSystems * gameSystems) { _gameSystems = gameSystems; }
        void SetPipeSpawner(Entity pipeSpawner) { _pipeSpawner = pipeSpawner; }
        void SetPlayer(Entity player) { _player = player; }
        void SetGetReady(Entity getReady) { _getReady = getReady; }
    protected:
        /**
         * @brief InputComponent that defines behavior for this input handler.
         */
        FlappyInputComponent * _component;
        /**
         * @brief StateMachine that controls which input handling functions
         *        are called.
         */
        SharedMachine<FlappyInputHandler, void> _machine;
        /**
         * @brief Current MachineState the state machine is in.
         */
        MachineState _curState;
        /**
         * @brief Used to change the screen when you restart the game.
         */
        ScreenManager & _screenManager;
        /**
         * @brief Game Systems for Flappy Bird.
         */
        FlappyGameSystems * _gameSystems;
        /**
         * @brief Entity that is the player
         */
        Entity _player;
        /**
         * @brief Entity that is the pipe spawner
         */
        Entity _pipeSpawner;
        /**
         * @brief Entity that is the get ready overlay.
         */
        Entity _getReady;

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
        
        /**
         * @brief Checks the allowed states that can be transitioned to if the current
         *        state is FlappyStates::GameIntro
         *
         * @param newState The new MachineState that the machine is told to move to.
         *
         * @return true if the transition is allowed, otherwise false;
         */
        bool GameIntroTransitionCheck(const MachineState & newState);

        /**
         * @brief Defines how the input should be handled when the current state
         *        is FlappyStates::InAir.
         */
        virtual void InAirInput(MachineState & curState)  {}

        /**
         * @brief Defines how the input should be handled when the current state
         *        is FlappyStates::OnGround.
         */
        virtual void OnGroundInput(MachineState & curState) {}

        /**
         * @brief Defiens how the input should be handled when the current state
         *       is FlappyStates::GameIntro
         */
        virtual void GameIntroInput(MachineState & curState) {}
};

}

#endif
