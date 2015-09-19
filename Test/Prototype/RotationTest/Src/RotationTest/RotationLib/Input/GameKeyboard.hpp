#ifndef Rotation_Input_GameKeyboard_H_
#define Rotation_Input_GameKeyboard_H_

#include "RotationInputHandler.hpp"

namespace ild
{

/**
 * @brief Keyboard handler for RotationTest
 */
class GameKeyboard: public RotationInputHandler
{
    public:
        /**
         * @brief Captures input and calls out to the inputComponent's actions.
         */
        virtual void HandleInput() override;
};

}

#endif
