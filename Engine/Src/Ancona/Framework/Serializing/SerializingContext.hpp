#ifndef Ancona_Engine_Serializing_SerializingContext_H_
#define Ancona_Engine_Serializing_SerializingContext_H_

#include <Ancona/Framework/Systems/ScreenSystemsContainer.hpp>

namespace ild
{

/**
 * @brief Holds the contextual objects used in the current loading operation.
 *
 * @author Jeff Swenson
 * @author Tucker Lein
 */
class SerializingContext
{
    public:
        /**
         * @brief Construct the SerializingContext.
         *
         * @param systems System container for the screen.
         */
        SerializingContext(ScreenSystemsContainer & systems);


        /* getters and setters */
        ScreenSystemsContainer & systems() { return _systems; }
    private:
        ScreenSystemsContainer & _systems;

};

}

#endif
