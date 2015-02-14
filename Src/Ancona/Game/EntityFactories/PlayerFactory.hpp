#ifndef Ancona_Game_EntityFactories_PlayerFactory_H_
#define Ancona_Game_EntityFactories_PlayerFactory_H_

#include <map>
#include <string>

#include <Ancona/Game/Systems/GameSystems.hpp>

namespace ild
{

namespace factories
{
    Entity CreatePlayer(
            GameSystems * gameSystems,
            Entity camera,
            std::map<std::string, CollisionType> collisionTypes);

    void SetupCollisions(
            Entity player,
            GameSystems * gameSystems,
            std::map<std::string, CollisionType> collisionTypes);

    std::function<void(Entity player, Entity ground)> GroundCollisionHandler(GameSystems * gameSystems);

}

}

#endif
