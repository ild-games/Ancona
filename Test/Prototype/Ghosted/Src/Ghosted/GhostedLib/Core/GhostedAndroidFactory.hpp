#ifndef Ghosted_Core_GhostedAndroidFactory_H_
#define Ghosted_Core_GhostedAndroidFactory_H_

#include "GhostedPlatformFactory.hpp"
#include "../Input/GameTouch.hpp"

namespace ild
{

/**
 * @brief Everything needed to run on the Android platform.
 */
class GhostedAndroidFactory : public GhostedPlatformFactory
{
    public:
        /* getters and setters */
        GameTouch * inputHandler() override;
};

}

#endif
