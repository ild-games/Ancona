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
    drawableSystem.CreateSpriteComponent(
            ground, 
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

/* Foreground Entity */
Entity factories::CreateForeground(
        SystemManager & manager,
        PositionSystem & positionSystem,
        DrawableSystem & drawableSystem)
{
    Entity foreground = manager.CreateEntity();
    factories::SetupForegroundPosition(foreground, positionSystem);
    factories::SetupForegroundSprite(foreground, drawableSystem);
    return foreground;
}

void factories::SetupForegroundPosition(
        Entity foreground,
        PositionSystem & positionSystem)
{
    PositionComponent * fgPos = positionSystem.CreateComponent(foreground);
    fgPos->Position.x = 136;
    fgPos->Position.y = 200;
}

void factories::SetupForegroundSprite(
        Entity foreground,
        DrawableSystem & drawableSystem)
{
    drawableSystem.CreateSpriteComponent(
            foreground, 
            "flappy-fg",
            RenderPriority::Background, 1);
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
    if(rand() % 2)
    {
        drawableSystem.CreateSpriteComponent(
                background, 
                "flappy-bg1",
                RenderPriority::Background);
    } 
    else 
    {
        drawableSystem.CreateSpriteComponent(
                background, 
                "flappy-bg2",
                RenderPriority::Background);
    }
}

/* Point Counter Entity */
std::vector<Entity> factories::CreatePointCounter(
        SystemManager & manager,
        PositionSystem & positionSystem,
        DrawableSystem & drawableSystem)
{
    Entity pointCounterPlain = manager.CreateEntity();
    Entity pointCounterBorder = manager.CreateEntity();
    std::vector<Entity> pointCounters;
    pointCounters.push_back(pointCounterPlain);
    pointCounters.push_back(pointCounterBorder);
    factories::SetupPointCounterPosition(pointCounters, positionSystem);
    factories::SetupPointCounterText(pointCounters, drawableSystem);
    return pointCounters;
}


void factories::SetupPointCounterPosition(
        std::vector<Entity> pointCounters,
        PositionSystem & position)
{
    PositionComponent * pointCounterPos1 = position.CreateComponent(pointCounters[0]);
    pointCounterPos1->Position.x = 80;
    pointCounterPos1->Position.y = 320;
    PositionComponent * pointCounterPos2 = position.CreateComponent(pointCounters[1]);
    pointCounterPos2->Position.x = 80;
    pointCounterPos2->Position.y = 320;
}

void factories::SetupPointCounterText(
        std::vector<Entity> pointCounters,
        DrawableSystem & drawableSystem)
{
    drawableSystem.CreateTextComponent(
            pointCounters[0],
            "0",
            "dimitri-plain",
            sf::Color::White,
            30,
            RenderPriority::Foreground,
            100,
            false);
    drawableSystem.CreateTextComponent(
            pointCounters[1],
            "0",
            "dimitri-border",
            sf::Color::Black,
            30,
            RenderPriority::Foreground,
            101,
            false);
}
