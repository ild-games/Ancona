#ifndef Rotation_Core_RotationDesktopFactory_H_
#define Rotation_Core_RotationDesktopFactory_H_

#include "RotationPlatformFactory.hpp"
#include "../Input/GameKeyboard.hpp"

namespace ild
{

/**
 * @brief Everything needed to run on the Desktop platform.
 */
class RotationDesktopFactory : public RotationPlatformFactory
{
    public:
        /* getters and setters */
        GameKeyboard * inputHandler() override;
};

}

#endif
