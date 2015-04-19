#ifndef Test_Prototype_FlappyBirdTest_InputDevices_FlappyTouch_H_
#define Test_Prototype_FlappyBirdTest_InputDevices_FlappyTouch_H_

#include <Ancona/Framework/Screens/ScreenManager.hpp>
#include "FlappyInputHandler.hpp"
#include "../Screens/FlappyScreen.hpp"
#include "../States/FlappyStates.hpp"

namespace ild 
{

class FlappyTouch : public FlappyInputHandler
{
    public:
        FlappyTouch(
                ScreenManager & screenManager,
                MachineState initialState = FlappyStates::GameIntro);

    protected:
        void InAirInput(MachineState & curState);

        void OnGroundInput(MachineState & curState);

        void GameIntroInput(MachineState & curState);
};

}

#endif
