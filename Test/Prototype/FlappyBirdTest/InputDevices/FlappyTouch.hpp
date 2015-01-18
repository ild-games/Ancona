#ifndef Test_Prototype_FlappyBirdTest_InputDevices_FlappyTouch_H_
#define Test_Prototype_FlappyBirdTest_InputDevices_FlappyTouch_H_

#include <Ancona/Engine/InputDevices/InputHandler.hpp>
#include <Ancona/Util/StateMachine/SharedMachine.hpp>
#include "../States/FlappyStates.hpp"
#include <Ancona/Engine/Screen/ScreenManager.hpp>
#include "../Screen/TestScreen.hpp"
#include <vector>

namespace ild 
{

class FlappyInputComponent;

class FlappyTouch : public InputHandler
{
    public:
        FlappyTouch(ScreenManager & screenManager);

        void HandleInput();

        void InAirInput(MachineState & curState);

        void OnGroundInput(MachineState & curState);

        void RegisterInputComponent(FlappyInputComponent * component);
        
        void ChangeState(const MachineState & newState);

    private:
        FlappyInputComponent * _component;

        SharedMachine<FlappyTouch, void> _machine;

        MachineState _curState;

        ScreenManager & _screenManager;

        bool AllowedTransition(const MachineState & newState);

        bool InAirTransitionCheck(const MachineState & newState);
};

}

#endif
