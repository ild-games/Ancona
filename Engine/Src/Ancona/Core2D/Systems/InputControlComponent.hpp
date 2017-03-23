#ifndef Ancona_Engine_Config_Systems_InputControlComponent_H_
#define Ancona_Engine_Config_Systems_InputControlComponent_H_

#include <Ancona/Core2D/InputDevices/InputHandler.hpp>

namespace ild
{

/**
 * @brief  A component used to control the player using a device 
 *         (keyboard, mouse, ...) should inherit from this class
 *
 * @author Jeff Swenson, Tucker Lein
 */
class InputControlComponent 
{
    public:
        /**
         * @brief Constructs the component with an input handler
         *
         * @param handler InputHandler for the component
         */
        InputControlComponent(InputHandler & handler);

        /**
         * @brief Updates the component's input handler
         *
         * @param delta milliseconds since last update
         */
        void Update(float delta);

        /* getters and setters */
        InputHandler & handler() { return _handler; }
    private:
        /**
         * @brief Input handler that handles the input gathering
         *        for this component
         */
        InputHandler & _handler;
};

}

#endif
