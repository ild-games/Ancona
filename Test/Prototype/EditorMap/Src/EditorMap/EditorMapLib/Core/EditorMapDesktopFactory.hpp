#ifndef EditorMap_Core_EditorMapDesktopFactory_H_
#define EditorMap_Core_EditorMapDesktopFactory_H_

#include "EditorMapPlatformFactory.hpp"
#include "../Input/GameKeyboard.hpp"

namespace ild
{

/**
 * @brief Everything needed to run on the Desktop platform.
 */
class EditorMapDesktopFactory : public EditorMapPlatformFactory
{
    public:
        /* getters and setters */
        GameKeyboard * inputHandler() override;
};

}

#endif
