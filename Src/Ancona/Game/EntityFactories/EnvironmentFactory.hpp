#ifndef Ancona_Game_EntityFactories_EnvironmentFactory_H_
#define Ancona_Game_EntityFactories_EnvironmentFactory_H_

#include <map>

#include <SFML/Window.hpp>

#include <Ancona/Game/Systems/GameScreenSystems.hpp>

namespace ild
{

namespace factories
{
    Entity CreateScreenCamera(
            GameScreenSystems & gameSystems,
            const sf::View & originalView);

    Entity CreateGround(
            GameScreenSystems & gameSystems,
            std::map<std::string, CollisionType> collisionTypes);

}

}

#endif
