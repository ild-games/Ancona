#ifndef Ancona_Game_InputDevices_FlappyKeyboard_H_
#define Ancona_Game_InputDevices_FlappyKeyboard_H_

#include <Ancona/Engine/Screens/ScreenManager.hpp>
#include "FlappyInputHandler.hpp"
#include "../Screens/FlappyScreen.hpp"
#include "../States/FlappyStates.hpp"


namespace ild
{

/**
 * @brief Defines the input handling for the keyboard in FlappyBird. 
 *
 * @author Tucker Lein
 */
class FlappyKeyboard : public FlappyInputHandler
{
    public:
        FlappyKeyboard(
                ScreenManager & screenManager,
                MachineState initialState = FlappyStates::GameIntro);

    protected:
        void InAirInput(MachineState & curState);

        void OnGroundInput(MachineState & curState);

        void GameIntroInput(MachineState & curState);
};

}

#endif
