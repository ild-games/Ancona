#ifndef Ghosted_Core_GhostedPlatformFactory_H_
#define Ghosted_Core_GhostedPlatformFactory_H_

#include "../Input/GhostedInputHandler.hpp"

namespace ild
{

/**
 * @brief Defines everything all platforms must provide to run the game on
 */
class GhostedPlatformFactory
{
    public:
        /* getters and setters */
        virtual GhostedInputHandler * inputHandler() = 0;

};

}

#endif
