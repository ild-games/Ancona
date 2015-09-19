#ifndef Rotation_Core_RotationPlatformFactory_H_
#define Rotation_Core_RotationPlatformFactory_H_

#include "../Input/RotationInputHandler.hpp"

namespace ild
{

/**
 * @brief Defines everything all platforms must provide to run the game on
 */
class RotationPlatformFactory
{
    public:
        /* getters and setters */
        virtual RotationInputHandler * inputHandler() = 0;

};

}

#endif
