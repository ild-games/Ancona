#ifndef Ancona_Game_EntityFactories_PlayerFactory_H_
#define Ancona_Game_EntityFactories_PlayerFactory_H_

#include <map>
#include <string>

#include <QJack/GameLib/Systems/GameScreenSystems.hpp>

namespace ild
{

namespace factories
{
    Entity CreatePlayer(
            GameScreenSystems & gameSystems,
            std::map<std::string, CollisionType> collisionTypes);

    void SetupCollisions(
            Entity player,
            GameScreenSystems & gameSystems,
            std::map<std::string, CollisionType> collisionTypes);

    std::function<void(Entity player, Entity ground)> GroundCollisionHandler(GameScreenSystems * gameSystems);

}

}

#endif
