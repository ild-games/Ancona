#ifndef Ancona_Game_InputDevices_PlayerKeyboard_H_
#define Ancona_Game_InputDevices_PlayerKeyboard_H_

#include <Ancona/Engine/InputDevices/InputHandler.hpp>

namespace ild 
{

class PlayerInputComponent;

/**
 * @brief Gathers input for the player using the keyboard.
 *
 * @owner Tucker Lein
 */
class PlayerKeyboard : public InputHandler
{
    public:
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

        /**
         * @brief StateMachine that controls which input handling 
         *        functions are called.
         */
        //SharedMachine<PlayerKeyboard, void> _machine;
};

}

#endif
