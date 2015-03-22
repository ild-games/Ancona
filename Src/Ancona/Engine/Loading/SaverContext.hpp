#ifndef Ancona_Engine_Loading_SaverContext_H_
#define Ancona_Engine_Loading_SaverContext_H_

#include <Ancona/Engine/Core/Systems/ScreenSystemsContainer.hpp>
#include <Ancona/Engine/Loading/SaverMap.hpp>

namespace ild
{

/**
 * @brief Hoolds the contextual objects used in the current saving operation.
 *
 * @author Tucker Lein
 */
class SaverContext
{
    public:
        /**
         * @brief Construct the SaverContext.
         *
         * @param systems System container for the screen.
         */
        SaverContext(ScreenSystemsContainer & systems);

        /* getters and setters */
        SaverMap & GetSaverMap() { return _saverMap; }
        ScreenSystemsContainer & GetSystems() { return _systems; }
    private:
        SaverMap _saverMap;
        ScreenSystemsContainer & _systems;

};

}

#endif
