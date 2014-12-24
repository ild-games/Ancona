#ifndef Ancona_Game_InputDevices_FlappyKeyboard_H_
#define Ancona_Game_InputDevices_FlappyKeyboard_H_

#include <Ancona/Engine/InputDevices/InputHandler.hpp>
#include <Ancona/Util/StateMachine/SharedMachine.hpp>
#include "../States/FlappyStates.hpp"
#include <Ancona/Engine/Screen/ScreenManager.hpp>
#include "../Screen/TestScreen.hpp"

namespace ild
{

class FlappyInputComponent;

class FlappyKeyboard : public InputHandler
{
    public:
        FlappyKeyboard(ScreenManager & screenManager);

        void HandleInput();

        void InAirInput(MachineState & curState);

        void OnGroundInput(MachineState & curState);

        void RegisterInputComponent(
                FlappyInputComponent * component);

        void ChangeState(const MachineState & newState);

    private:

        FlappyInputComponent * _component;

        SharedMachine<FlappyKeyboard, void> _machine;

        MachineState _curState;

        ScreenManager & _screenManager;
};

}

#endif
