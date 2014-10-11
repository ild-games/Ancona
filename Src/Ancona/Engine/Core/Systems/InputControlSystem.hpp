#ifndef Ancona_Engine_Config_Systems_InputControlSystem_H_
#define Ancona_Engine_Config_Systems_InputControlSystem_H_

#include <Ancona/Engine/EntityFramework/UnorderedSystem.hpp>

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

        void Update(float delta);
};

}
#endif
