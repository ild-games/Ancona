#ifndef Test_Prototype_FlappyBirdTest_InputDevices_FlappyTouch_H_
#define Test_Prototype_FlappyBirdTest_InputDevices_FlappyTouch_H_

#include <Ancona/Engine/Screens/ScreenManager.hpp>
#include "FlappyInputHandler.hpp"
#include "../Screens/FlappyScreen.hpp"
#include "../States/FlappyStates.hpp"

namespace ild 
{

class FlappyTouch : public FlappyInputHandler
{
    public:
        FlappyTouch(ScreenManager & screenManager);

    protected:
        void InAirInput(MachineState & curState);

        void OnGroundInput(MachineState & curState);
};

}

#endif
