#ifndef EditorMap_Input_GameKeyboard_H_
#define EditorMap_Input_GameKeyboard_H_

#include "EditorMapInputHandler.hpp"

namespace ild
{

/**
 * @brief Keyboard handler for EditorMap
 */
class GameKeyboard: public EditorMapInputHandler
{
    public:
        /**
         * @brief Captures input and calls out to the inputComponent's actions.
         */
        virtual void HandleInput() override;
};

}

#endif
