#include <Ancona/Game/EntityFactories/EnvironmentFactory.hpp>

using namespace ild;

Entity factories::CreateGround(
        GameSystems * gameSystems,
        std::map<std::string, CollisionType> collisionTypes)
{
    Entity ground = gameSystems->GetManager().CreateEntity();

    // position component 
    gameSystems->GetPosition().CreateComponent(ground);
    PositionComponent * position = gameSystems->GetPosition().at(ground);
    position->Position.x = 100;
    position->Position.y = 500;

    // sprite component
    DrawableComponent * drawable = gameSystems->GetDrawable().CreateComponent(ground);
    drawable->AddSprite(
            "ground-sprite",
            "flappy-ground",
            RenderPriority::Player,
            -1);

    // collision component
    gameSystems->GetCollision().CreateComponent(
            ground,
            sf::Vector3f(540, 80, 0),
            collisionTypes["ground"]);

    return ground;
}
