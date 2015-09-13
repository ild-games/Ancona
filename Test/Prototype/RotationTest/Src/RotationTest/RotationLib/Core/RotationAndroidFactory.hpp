#ifndef Rotation_Core_RotationAndroidFactory_H_
#define Rotation_Core_RotationAndroidFactory_H_

#include "RotationPlatformFactory.hpp"
#include "../Input/GameTouch.hpp"

namespace ild
{

/**
 * @brief Everything needed to run on the Android platform.
 */
class RotationAndroidFactory : public RotationPlatformFactory
{
    public:
        /* getters and setters */
        GameTouch * inputHandler() override;
};

}

#endif
