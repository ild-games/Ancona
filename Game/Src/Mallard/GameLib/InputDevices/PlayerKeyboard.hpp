#ifndef Ancona_Game_InputDevices_PlayerKeyboard_H_
#define Ancona_Game_InputDevices_PlayerKeyboard_H_

#include <Ancona/Core2D/InputDevices/InputHandler.hpp>
#include <Ancona/Framework/Screens/ScreenManager.hpp>

namespace ild 
{

class PlayerInputComponent;

/**
 * @brief Gathers input for the player using the keyboard.
 *
 * @author Tucker Lein
 */
class PlayerKeyboard : public InputHandler
{
    public:
        PlayerKeyboard(ScreenManager & screenManager);

        /**
         * @see Ancona/Engine/InputDevices/InputHandler.hpp
         */
        void HandleInput();

        /**
         * @brief 
         *
         * @param component
         */
        void RegisterInputComponent(
                PlayerInputComponent * component);

    private:
        PlayerInputComponent * _component;
        ScreenManager & _screenManager;
};

}

#endif
