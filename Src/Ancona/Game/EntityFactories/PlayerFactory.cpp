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
    position->Position.x = 50;
    position->Position.y = 0;

    // sprite component
    DrawableComponent * drawable = gameSystems->GetDrawable().CreateComponent(player);
    drawable->AddShape(
            "player-shape",
            *new sf::RectangleShape(sf::Vector2f(16.0f, 17.0f)),
            RenderPriority::Player,
            -1);
    drawable->AddAnimation(
            "player-animation",
            "player-walking",
            RenderPriority::Player,
            sf::Vector2f(16.0f, 17.0f),
            6,
            0.1f);

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
            sf::Vector3f(17.0f, 17.0f, 0),
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
