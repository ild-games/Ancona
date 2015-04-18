#include <Ancona/Game/EntityFactories/PlayerFactory.hpp>

using namespace ild;

Entity factories::CreatePlayer(
        GameScreenSystems & gameSystems,
        std::map<std::string, CollisionType> collisionTypes)
{
    // collision component
    factories::SetupCollisions(
            gameSystems.GetSystemManager().GetEntity("player"),
            gameSystems,
            collisionTypes);

    return gameSystems.GetSystemManager().GetEntity("player");
}

void factories::SetupCollisions(
        Entity player,
        GameScreenSystems & gameSystems,
        std::map<std::string, CollisionType> collisionTypes)
{ 
    gameSystems.GetCollision().CreateComponent(
            player,
            sf::Vector3f(17.0f, 17.0f, 0),
            collisionTypes["player"]);

    /* Collision Handlers */
    // ground collision
    gameSystems.GetCollision().DefineCollisionCallback(
            collisionTypes["player"],
            collisionTypes["ground"],
            factories::GroundCollisionHandler(&gameSystems));
}

std::function<void(Entity player, Entity ground)> factories::GroundCollisionHandler(GameScreenSystems * gameSystems)
{
    return [gameSystems](Entity player, Entity ground)
    {
        auto & actions = gameSystems->GetPhysics().at(player)->GetActions();
        actions.StopFall();
        actions.SetAffectedByGravity(false);
    };
}
