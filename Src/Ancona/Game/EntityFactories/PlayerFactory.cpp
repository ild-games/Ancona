#include <Ancona/Game/EntityFactories/PlayerFactory.hpp>

using namespace ild;

Entity factories::CreatePlayer(
        GameSystems * gameSystems,
        std::map<std::string, CollisionType> collisionTypes)
{
    Entity player = gameSystems->GetManager().CreateEntity();

    // position component
    PlatformPhysicsComponent * position = gameSystems->GetPhysics().CreateComponent(player);
    //position->GetActions().CreatePositionAction()->Value(Point(50,0));
    position->GetActions().CreatePositionAction()
        ->Value(Point(50,20))
        ->Tween(3)
        ->Duration(5);
        

    // sprite component
    DrawableComponent * drawable = 
        gameSystems->GetDrawable().CreateComponent(player);
    drawable->AddDrawable(
            "player-shape",
            new ShapeDrawable(
                *position,
                *new sf::RectangleShape(sf::Vector2f(16.0f, 17.0f)),
                RenderPriority::Player,
                -1));
    drawable->AddDrawable(
            "player-animation",
            new AnimatedDrawable(
                *position,
                "player-walking",
                RenderPriority::Player,
                sf::Vector2f(16.0f, 17.0f),
                6,
                0.1f));

    // gravity component 
    position->GetActions().SetAffectedByGravity(true);

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
        auto & actions = gameSystems->GetPhysics().at(player)->GetActions();
        actions.StopFall();
        actions.SetAffectedByGravity(false);

    };
}
