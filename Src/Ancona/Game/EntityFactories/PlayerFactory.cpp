#include <Ancona/Game/EntityFactories/PlayerFactory.hpp>

using namespace ild;

Entity factories::CreatePlayer(
        GameSystems * gameSystems,
        std::map<std::string, CollisionType> collisionTypes)
{
    Entity player = gameSystems->GetManager().CreateEntity();

    // position component
    gameSystems->GetPosition().CreateComponent(player);
    PositionComponent * position = gameSystems->GetPosition().at(player);
    position->Position.x = 200;
    position->Position.y = 200;

    // sprite component
    gameSystems->GetDrawable().CreateSpriteComponent(
            player, 
            "player",
            RenderPriority::Player);

    // gravity component 
    gameSystems->GetSimpleGravity().CreateComponent(
            player, 
            *position);

    // collision component
    factories::SetupCollisions(
            player,
            gameSystems,
            collisionTypes);

    return player;
}

void factories::SetupCollisions(
        Entity player,
        GameSystems * gameSystems,
        std::map<std::string, CollisionType> collisionTypes)
{ 
    gameSystems->GetCollision().CreateComponent(
            player,
            sf::Vector3f(14.0f, 14.0f, 0),
            collisionTypes["player"]);

    /* Collision Handlers */
    // ground collision
    gameSystems->GetCollision().SetHandler(
            collisionTypes["player"],
            collisionTypes["ground"],
            factories::GroundCollisionHandler(gameSystems));
}

std::function<void(Entity player, Entity ground)> factories::GroundCollisionHandler(GameSystems * gameSystems)
{
    return [gameSystems](Entity player, Entity ground)
    {
        gameSystems->GetPosition().at(player)->Velocity.y = 0; 
    };
}
