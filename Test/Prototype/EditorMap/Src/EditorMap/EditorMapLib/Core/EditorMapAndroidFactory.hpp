#ifndef EditorMap_Core_EditorMapAndroidFactory_H_
#define EditorMap_Core_EditorMapAndroidFactory_H_

#include "EditorMapPlatformFactory.hpp"
#include "../Input/GameTouch.hpp"

namespace ild
{

/**
 * @brief Everything needed to run on the Android platform.
 */
class EditorMapAndroidFactory : public EditorMapPlatformFactory
{
    public:
        /* getters and setters */
        GameTouch * inputHandler() override;
};

}

#endif
