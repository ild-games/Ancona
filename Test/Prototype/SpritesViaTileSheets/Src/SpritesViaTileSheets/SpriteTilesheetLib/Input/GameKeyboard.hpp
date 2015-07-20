#ifndef SpriteTilesheet_Input_GameKeyboard_H_
#define SpriteTilesheet_Input_GameKeyboard_H_

#include "SpriteTilesheetInputHandler.hpp"

namespace ild
{

/**
 * @brief Keyboard handler for SpritesViaTileSheets
 */
class GameKeyboard: public SpriteTilesheetInputHandler
{
    public:
        /**
         * @brief Captures input and calls out to the inputComponent's actions.
         */
        virtual void HandleInput() override;
};

}

#endif
