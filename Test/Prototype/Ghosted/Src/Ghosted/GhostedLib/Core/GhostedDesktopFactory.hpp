#ifndef Ghosted_Core_GhostedDesktopFactory_H_
#define Ghosted_Core_GhostedDesktopFactory_H_

#include "GhostedPlatformFactory.hpp"
#include "../Input/GameKeyboard.hpp"

namespace ild
{

/**
 * @brief Everything needed to run on the Desktop platform.
 */
class GhostedDesktopFactory : public GhostedPlatformFactory
{
    public:
        /* getters and setters */
        GameKeyboard * inputHandler() override;
};

}

#endif
