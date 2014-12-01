#ifndef Ancona_Game_InputDevices_FlappyKeyboard_H_
#define Ancona_Game_InputDevices_FlappyKeyboard_H_

#include <Ancona/Engine/InputDevices/InputHandler.hpp>

namespace ild
{

class FlappyInputComponent;

class FlappyKeyboard : public InputHandler
{
    public:
        void HandleInput();

        void RegisterInputComponent(
                FlappyInputComponent * component);

    private:

        FlappyInputComponent * _component;
};

}

#endif
