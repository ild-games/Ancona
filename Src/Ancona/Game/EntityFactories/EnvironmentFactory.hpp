#ifndef Ancona_Game_EntityFactories_EnvironmentFactory_H_
#define Ancona_Game_EntityFactories_EnvironmentFactory_H_

#include <map>

#include <Ancona/Game/Systems/GameSystems.hpp>

namespace ild
{

namespace factories
{

    /**
     * @brief 
     *
     * @param gameSystems
     * @param collisionTypes
     *
     * @return 
     */
    Entity CreateGround(
            GameSystems * gameSystems,
            std::map<std::string, CollisionType> collisionTypes);

}

}

#endif
