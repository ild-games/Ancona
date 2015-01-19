#ifndef Ancona_Game_Core_Systems_GravitySystem_H_
#define Ancona_Game_Core_Systems_GravitySystem_H_

#include <Ancona/Engine/EntityFramework/UnorderedSystem.hpp>
#include "GravityComponent.hpp"

#include <SFML/System.hpp>

namespace ild
{

class GravitySystem : public UnorderedSystem<GravityComponent>
{
    public:
        GravitySystem(SystemManager & manager);

        void Update(float delta);

        GravityComponent * CreateComponent(
                const Entity & entity,
                PositionComponent & positionComponent);
};

}

#endif
