#include <Ancona/Game/EntityFactories/EnvironmentFactory.hpp>

using namespace ild;

Entity factories::CreateScreenCamera(
        GameScreenSystems & gameSystems,
        const sf::View & originalView)
{
    Entity cam = gameSystems.GetManager().CreateEntity();

    gameSystems.GetCamera().CreateComponent(
            cam,
            originalView,
            0,
            2.0f);

    return cam;
}

Entity factories::CreateGround(
        GameScreenSystems & gameSystems,
        std::map<std::string, CollisionType> collisionTypes)
{
    // sprite component
    DrawableComponent * drawable = 
        gameSystems.GetDrawable().CreateComponent(gameSystems.GetManager().GetEntity("ground"));
    drawable->AddDrawable(
            "ground-sprite",
            new SpriteDrawable(
                *gameSystems.GetPhysics()[gameSystems.GetManager().GetEntity("ground")],
                "flappy-ground",
                RenderPriority::Player,
                -1));

    // collision component
    gameSystems.GetCollision().CreateComponent(
            gameSystems.GetManager().GetEntity("ground"),
            sf::Vector3f(540, 80, 0),
            collisionTypes["ground"]);

    return gameSystems.GetManager().GetEntity("ground");
}
