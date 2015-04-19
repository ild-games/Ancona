#include <QJack/GameLib/EntityFactories/EnvironmentFactory.hpp>

using namespace ild;

Entity factories::CreateGround(
        GameScreenSystems & gameSystems,
        std::map<std::string, CollisionType> collisionTypes)
{
    // collision component
    gameSystems.collision().CreateComponent(
            gameSystems.systemManager().GetEntity("ground"),
            sf::Vector3f(540, 80, 0),
            collisionTypes["ground"]);

    return gameSystems.systemManager().GetEntity("ground");
}
