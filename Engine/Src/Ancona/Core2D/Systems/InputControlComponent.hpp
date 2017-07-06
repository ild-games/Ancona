#ifndef Ancona_Engine_Config_Systems_InputControlComponent_H_
#define Ancona_Engine_Config_Systems_InputControlComponent_H_

#include <memory>

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
        InputControlComponent() {}
        /**
         * @brief Constructs the component with an input handler
         *
         * @param handler InputHandler for the component
         */
        InputControlComponent(std::shared_ptr<InputHandler> handler);

        /**
         * @brief Updates the component's input handler
         *
         * @param delta milliseconds since last update
         */
        void Update(float delta);

        /* getters and setters */
        InputHandler & handler() { return *_handler; }
        void handler(std::shared_ptr<InputHandler> handler) { _handler = handler; }
    private:
        /**
         * @brief Input handler that handles the input gathering
         *        for this component
         */
        std::shared_ptr<InputHandler> _handler;
};

}

#endif
