#ifndef EditorMap_Input_GameTouch_H_
#define EditorMap_Input_GameTouch_H_

#include "EditorMapInputHandler.hpp"

namespace ild
{

/**
 * @brief Touch input handler for EditorMap
 */
class GameTouch: public EditorMapInputHandler
{
    public:
        /**
         * @brief Captures input and calls out to the inputComponent's actions.
         */
        virtual void HandleInput() override;
};

}

#endif
