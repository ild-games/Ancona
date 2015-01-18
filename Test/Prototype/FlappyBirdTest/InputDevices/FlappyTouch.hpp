#ifndef Test_Prototype_FlappyBirdTest_InputDevices_FlappyTouch_H_
#define Test_Prototype_FlappyBirdTest_InputDevices_FlappyTouch_H_

#include <Ancona/Engine/InputDevices/InputHandler.hpp>
#include <Ancona/Util/StateMachine/SharedMachine.hpp>

namespace ild 
{

class FlappyInputComponent;

class FlappyTouch : public InputHandler
{
    public:
        void HandleInput();

        //void InAirInput(MachineState & curState);

        //void OnGroundInput(MachineState & curState);

        void RegisterInputComponent(FlappyInputComponent * component);

        //void ChangeState(const MachineState & newState);

    private:
        FlappyInputComponent * _component;

};

}

#endif
