#ifndef Ancona_Engine_Loading_LoadingContext_H_
#define Ancona_Engine_Loading_LoadingContext_H_

#include <Ancona/Engine/Loading/InflaterMap.hpp>
#include <Ancona/Engine/EntityFramework/SystemManager.hpp>

namespace ild
{

/**
 * @brief Holds the contextual objects used in the current loading operation.
 *
 * @author Jeff Swenson
 * @author Tucker Lein
 */
class LoadingContext 
{
    public:
        /**
         * @brief Construct the LoadingContext.
         *
         * @param systems SystemManager for the screen.
         */
        LoadingContext(SystemManager & systems);

        /* getters and setters */
        InflaterMap & GetInflaterMap() { return _inflaterMap; }
    private:
        InflaterMap _inflaterMap;
};

}

#endif
