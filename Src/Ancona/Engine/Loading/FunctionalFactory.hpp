#ifndef Ancona_Engine_Loading_FunctionalFactory_H_
#define Ancona_Engine_Loading_FunctionalFactory_H_

#include <jsoncpp/json/json.h>

#include <Ancona/Engine/Loading/LoadingContext.hpp>

namespace ild
{

/**
 * @brief Contains loaders and save functions for misc. objects such as external libraries.
 *
 * @author Tucker Lein
 */
namespace factories
{

    /**
     * @brief Inflater for a rectangle shape.
     */
    void * RectangleInflate(
            const Json::Value & object,
            const Entity entity,
            LoadingContext * loadingContext);

    /**
     * @brief Inflater for a circle shape.
     */
    void * CircleInflate(
            const Json::Value & object,
            const Entity entity,
            LoadingContext * loadingContext);

    /**
     * @brief Inflater for a position action.
     */
    void * PlatformerPositionActionInflate(
            const Json::Value & object,
            const Entity entity,
            LoadingContext * loadingContext);

    /**
     * @brief Inflater for a velocity action.
     */
    void * PlatformerVelocityActionInflate(
            const Json::Value & object,
            const Entity entity,
            LoadingContext * loadingContext);
}

}

#endif
