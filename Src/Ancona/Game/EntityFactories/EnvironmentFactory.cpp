#include <Ancona/Game/EntityFactories/EnvironmentFactory.hpp>

using namespace ild;

Entity factories::CreateGround(
        GameScreenSystems & gameSystems,
        std::map<std::string, CollisionType> collisionTypes)
{
    // collision component
    gameSystems.GetCollision().CreateComponent(
            gameSystems.GetSystemManager().GetEntity("ground"),
            sf::Vector3f(540, 80, 0),
            collisionTypes["ground"]);

    return gameSystems.GetSystemManager().GetEntity("ground");
}
