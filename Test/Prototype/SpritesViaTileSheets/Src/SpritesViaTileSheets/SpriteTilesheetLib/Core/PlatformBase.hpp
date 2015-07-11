#ifndef SpriteTilesheet_Core_PlatformBase_H_
#define SpriteTilesheet_Core_PlatformBase_H_

#include "../Input/SpriteTilesheetInputHandler.hpp"

namespace ild
{

/**
 * @brief Defines everything all platforms must provide to run the game on
 */
class PlatformBase
{
    public:
        /* getters and setters */
        virtual SpriteTilesheetInputHandler * inputHandler() = 0;

};

}

#endif
