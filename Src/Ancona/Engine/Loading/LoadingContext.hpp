#ifndef Ancona_Engine_Loading_LoadingContext_H_
#define Ancona_Engine_Loading_LoadingContext_H_

#include <Ancona/Engine/Systems/ScreenSystemsContainer.hpp>

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
         * @param systems System container for the screen.
         */
        LoadingContext(ScreenSystemsContainer & systems);


        /* getters and setters */
        ScreenSystemsContainer & GetSystems() { return _systems; }
    private:
        ScreenSystemsContainer & _systems;

};

}

#endif
