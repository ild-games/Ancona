#include "EnvironmentFactory.hpp"

#include <random>

using namespace ild;

/* Ground Entity */
Entity factories::CreateGround(
        SystemManager & manager,
        PositionSystem & positionSystem,
        DrawableSystem & drawableSystem,
        CollisionSystem & collisionSystem,
        std::map<std::string, CollisionType> collisionTypes)
{
    Entity ground = manager.CreateEntity();
    Entity groundWarp = manager.CreateEntity();

    // position component
    factories::SetupGroundPosition(
            ground,
            groundWarp,
            positionSystem);

    // sprite component
    factories::SetupGroundSprite(
            ground,
            drawableSystem);

    // collision component
    factories::SetupGroundCollisions(
            ground,
            groundWarp,
            collisionTypes,
            collisionSystem,
            positionSystem);

    return ground;
}

void factories::SetupGroundPosition(
        Entity ground,
        Entity groundWarp,
        PositionSystem & positionSystem)
{
    PositionComponent * groundPosition = positionSystem.CreateComponent(ground);
    groundPosition->Position.y = 340.0f;
    groundPosition->Velocity.x = -65.0f;

    PositionComponent * groundWarpPosition = positionSystem.CreateComponent(groundWarp);
    groundWarpPosition->Position.x = -210.f;
    groundWarpPosition->Position.y = 340.0f;
}

void factories::SetupGroundSprite(
        Entity ground,
        DrawableSystem & drawableSystem)
{
    DrawableComponent * drawable = drawableSystem.CreateComponent(ground);
    drawable->AddSprite(
            "ground-srite",
            "flappy-ground",
            RenderPriority::Player,
            -1);
}

void factories::SetupGroundCollisions(
        Entity ground,
        Entity groundWarp,
        std::map<std::string, CollisionType> collisionTypes,
        CollisionSystem & collisionSystem,
        PositionSystem & positionSystem)
{
    collisionSystem.CreateComponent(
            ground,
            sf::Vector3f(540, 80, 0),
            collisionTypes["ground"]);
    collisionSystem.CreateComponent(
            groundWarp,
            sf::Vector3f(5, 5, 0),
            collisionTypes["groundWarp"]);
    collisionSystem.SetHandler(
            collisionTypes["ground"],
            collisionTypes["groundWarp"],
            factories::GroundToGroundWarpCollisionHandler(positionSystem));
}

std::function< void(Entity ground, Entity groundWarp) > factories::GroundToGroundWarpCollisionHandler(PositionSystem & positionSystem) 
{
    return [&positionSystem](Entity ground, Entity groundWarp)
    {
        positionSystem.at(ground)->Position.x = 270;
    };
}


/* Pipe Spawner Entity */
Entity factories::CreatePipeSpawner(
        SystemManager & manager,
        PipeSpawnerSystem & pipeSpawnerSystem,
        PositionSystem & positionSystem,
        DrawableSystem & drawableSystem,
        CollisionSystem & collisionSystem,
        std::map<std::string, CollisionType> collisionTypes)
{
    Entity pipeSpawner = manager.CreateEntity();
    pipeSpawnerSystem.CreateComponent(
            pipeSpawner,
            drawableSystem,
            positionSystem,
            collisionSystem,
            manager,
            collisionTypes["pipe"],
            collisionTypes["point"]);
    return pipeSpawner;
}

/* Background Entity */
Entity factories::CreateBackground(
        SystemManager & manager,
        PositionSystem & positionSystem,
        DrawableSystem & drawableSystem)
{
    Entity background = manager.CreateEntity();
    factories::SetupBackgroundPosition(background, positionSystem);
    factories::SetupBackgroundSprite(background, drawableSystem);
    return background;
}

void factories::SetupBackgroundPosition(
        Entity background,
        PositionSystem & positionSystem)
{
    PositionComponent * bgPos = positionSystem.CreateComponent(background);
    bgPos->Position.x = 320;
    bgPos->Position.y = 240;
}

void factories::SetupBackgroundSprite(
        Entity background,
        DrawableSystem & drawableSystem)
{
    DrawableComponent * drawable = drawableSystem.CreateComponent(background);
    std::string bgToUse;
    if(rand() % 2)
    {
        bgToUse = "flappy-bg1";
    } 
    else 
    {
        bgToUse = "flappy-bg2";
    }
    drawable->AddSprite(
            "bg-sprite",
            bgToUse,
            RenderPriority::Background);
    drawable->AddSprite(
            "fg-sprite",
            "flappy-fg",
            RenderPriority::Background,
            1,
            sf::Vector2f(-184.0f, -40.0f));
}

/* Point Counter Entity */
Entity factories::CreatePointCounter(
        SystemManager & manager,
        PositionSystem & positionSystem,
        DrawableSystem & drawableSystem)
{
    Entity pointCounter = manager.CreateEntity();
    factories::SetupPointCounterPosition(pointCounter, positionSystem);
    factories::SetupPointCounterText(pointCounter, drawableSystem);
    return pointCounter;
}


void factories::SetupPointCounterPosition(
        Entity pointCounter,
        PositionSystem & position)
{
    PositionComponent * pointCounterPos = position.CreateComponent(pointCounter);
    pointCounterPos->Position.x = 135;
    pointCounterPos->Position.y = 148; 
}

void factories::SetupPointCounterText(
        Entity pointCounter,
        DrawableSystem & drawableSystem)
{
    DrawableComponent * drawable = drawableSystem.CreateComponent(pointCounter);
    drawable->AddText(
            "plain-text",
            "0",
            "dimitri-plain",
            sf::Color::White,
            34,
            RenderPriority::Foreground,
            100,
            sf::Vector2f(0.0f, 0.0f),
            false);
    drawable->AddText(
            "border-text",
            "0",
            "dimitri-border",
            sf::Color::Black,
            34,
            RenderPriority::Foreground,
            101,
            sf::Vector2f(0.0f, 0.0f),
            false);
}
