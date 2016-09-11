#ifndef Ancona_Engine_InputDevices_InputHandler_H_
#define Ancona_Engine_InputDevices_InputHandler_H_

namespace ild
{

class InputControlComponent;

/**
 * @brief Abstract input handler used to collect input for
 *        specific actions
 *
 * @author Tucker Lein
 */
class InputHandler
{
    public:
        /**
         * @brief Gathers the input for this specific control
         *        device
         */
        virtual void HandleInput(float delta) = 0;
};

}

#endif
