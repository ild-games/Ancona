#include <Ancona/Game/EntityFactories/EnvironmentFactory.hpp>

using namespace ild;

Entity factories::CreateScreenCamera(
        GameSystems & gameSystems,
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
        GameSystems & gameSystems,
        std::map<std::string, CollisionType> collisionTypes)
{
    Entity ground = gameSystems.GetManager().CreateEntity();

    // position component 
    PlatformPhysicsComponent * physics = gameSystems.GetPhysics().CreateComponent(ground);

    auto & actions = physics->GetActions();
    actions.CreatePositionAction()
        ->Value(Point(100,500));
    actions.CreateVelocityAction()
        ->Value(Point(0,0.5))
        ->Duration(1);

    // sprite component
    DrawableComponent * drawable = 
        gameSystems.GetDrawable().CreateComponent(ground);
    drawable->AddDrawable(
            "ground-sprite",
            new SpriteDrawable(
                *physics,
                "flappy-ground",
                RenderPriority::Player,
                -1));

    // collision component
    gameSystems.GetCollision().CreateComponent(
            ground,
            sf::Vector3f(540, 80, 0),
            collisionTypes["ground"]);

    return ground;
}
