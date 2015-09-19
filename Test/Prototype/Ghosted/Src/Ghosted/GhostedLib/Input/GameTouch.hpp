#ifndef Ghosted_Input_GameTouch_H_
#define Ghosted_Input_GameTouch_H_

#include "GhostedInputHandler.hpp"

namespace ild
{

/**
 * @brief Touch input handler for Ghosted
 */
class GameTouch: public GhostedInputHandler
{
    public:
        /**
         * @brief Captures input and calls out to the inputComponent's actions.
         */
        virtual void HandleInput() override;
};

}

#endif
