#include <Ancona/Game/EntityFactories/PlayerFactory.hpp>

using namespace ild;

Entity factories::CreatePlayer(
        GameScreenSystems & gameSystems,
        std::map<std::string, CollisionType> collisionTypes)
{
    // sprite component
    DrawableComponent * drawable = 
        gameSystems.GetDrawable().CreateComponent(gameSystems.GetManager().GetEntity("player"));
    drawable->AddDrawable(
            "player-shape",
            new ShapeDrawable(
                *gameSystems.GetPhysics()[gameSystems.GetManager().GetEntity("player")],
                *new sf::RectangleShape(sf::Vector2f(16.0f, 17.0f)),
                RenderPriority::Player,
                -1));
    drawable->AddDrawable(
            "player-animation",
            new AnimatedDrawable(
                *gameSystems.GetPhysics()[gameSystems.GetManager().GetEntity("player")],
                "player-walking",
                RenderPriority::Player,
                sf::Vector2f(16.0f, 17.0f),
                6,
                0.1f));

    // collision component
    factories::SetupCollisions(
            gameSystems.GetManager().GetEntity("player"),
            gameSystems,
            collisionTypes);

    return gameSystems.GetManager().GetEntity("player");
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
    gameSystems.GetCollision().SetHandler(
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
