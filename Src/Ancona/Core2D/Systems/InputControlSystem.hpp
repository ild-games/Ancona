#ifndef Ancona_Engine_Config_Systems_InputControlSystem_H_
#define Ancona_Engine_Config_Systems_InputControlSystem_H_

#include <Ancona/Framework/EntityFramework/UnorderedSystem.hpp>

#include "InputControlComponent.hpp"

namespace ild
{

/**
 * @brief Used to provide the wiring for a player control component created 
 * in the game project.
 * @author Jeff Swenson
 */
class InputControlSystem : public UnorderedSystem<InputControlComponent>
{
    public:
        InputControlSystem(SystemManager & manager);

        /**
         * @brief Attach an InputControlComponent to the the 
         * entity.  The system will delete the component when
         * it is removed from the entity.
         *
         * @param entity Entity component will be attached to.
         * @param component Component to attach.
         */
        void AddComponent(const Entity & entity, 
                InputControlComponent * component);

        void Update(float delta);
};

}
#endif
