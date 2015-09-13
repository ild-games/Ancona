#ifndef Rotation_Input_GameTouch_H_
#define Rotation_Input_GameTouch_H_

#include "RotationInputHandler.hpp"

namespace ild
{

/**
 * @brief Touch input handler for RotationTest
 */
class GameTouch: public RotationInputHandler
{
    public:
        /**
         * @brief Captures input and calls out to the inputComponent's actions.
         */
        virtual void HandleInput() override;
};

}

#endif
