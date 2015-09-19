#ifndef Ghosted_Input_GameKeyboard_H_
#define Ghosted_Input_GameKeyboard_H_

#include "GhostedInputHandler.hpp"

namespace ild
{

/**
 * @brief Keyboard handler for Ghosted
 */
class GameKeyboard: public GhostedInputHandler
{
    public:
        /**
         * @brief Captures input and calls out to the inputComponent's actions.
         */
        virtual void HandleInput() override;
};

}

#endif
