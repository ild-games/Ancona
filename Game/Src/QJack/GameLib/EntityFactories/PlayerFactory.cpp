#include <QJack/GameLib/EntityFactories/PlayerFactory.hpp>

using namespace ild;

Entity factories::CreatePlayer(
        GameScreenSystems & gameSystems,
        std::map<std::string, CollisionType> collisionTypes)
{
    // collision component
    factories::SetupCollisions(
            gameSystems.systemManager().GetEntity("player"),
            gameSystems,
            collisionTypes);

    return gameSystems.systemManager().GetEntity("player");
}

void factories::SetupCollisions(
        Entity player,
        GameScreenSystems & gameSystems,
        std::map<std::string, CollisionType> collisionTypes)
{
    gameSystems.collision().CreateComponent(
            player,
            sf::Vector3f(17.0f, 17.0f, 0),
            collisionTypes["player"]);

    /* Collision Handlers */
    // ground collision
    gameSystems.collision().DefineCollisionCallback(
            collisionTypes["player"],
            collisionTypes["ground"],
            factories::GroundCollisionHandler(&gameSystems));
}

std::function<void(Entity player, Entity ground)> factories::GroundCollisionHandler(GameScreenSystems * gameSystems)
{
    return [gameSystems](Entity player, Entity ground)
    {
        auto & actions = gameSystems->physics().at(player)->actions();
        actions.StopFall();
        actions.SetAffectedByGravity(false);
    };
}
