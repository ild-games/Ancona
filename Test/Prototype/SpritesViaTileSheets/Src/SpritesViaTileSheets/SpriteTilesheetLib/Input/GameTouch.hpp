#ifndef SpriteTilesheet_Input_GameTouch_H_
#define SpriteTilesheet_Input_GameTouch_H_

#include "SpriteTilesheetInputHandler.hpp"

namespace ild
{

/**
 * @brief Touch input handler for SpritesViaTileSheets
 */
class GameTouch: public SpriteTilesheetInputHandler
{
    public:
        /**
         * @brief Captures input and calls out to the inputComponent's actions.
         */
        virtual void HandleInput() override;
};

}

#endif
