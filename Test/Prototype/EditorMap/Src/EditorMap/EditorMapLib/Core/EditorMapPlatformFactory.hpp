#ifndef EditorMap_Core_EditorMapPlatformFactory_H_
#define EditorMap_Core_EditorMapPlatformFactory_H_

#include "../Input/EditorMapInputHandler.hpp"

namespace ild
{

/**
 * @brief Defines everything all platforms must provide to run the game on
 */
class EditorMapPlatformFactory
{
    public:
        /* getters and setters */
        virtual EditorMapInputHandler * inputHandler() = 0;

};

}

#endif
