#include <Ancona/Engine/Core/Systems/Physics/PlatformPhysicsSystem.hpp>
#include <Ancona/Engine/Loading/FunctionalFactory.hpp>

using namespace ild;

void * factories::RectangleInflate(
        const Json::Value & object,
        const Entity & entity,
        LoadingContext * loadingContext)
{
    return new sf::RectangleShape(
            sf::Vector2f(
                object["width"].asFloat(),
                object["height"].asFloat()));
}

void * factories::CircleInflate(
        const Json::Value & object,
        const Entity & entity,
        LoadingContext * loadingContext)
{
    return new sf::CircleShape(object["radius"].asFloat());
}

void * factories::PlatformerPositionActionInflate(
    const Json::Value & object,
    const Entity & entity,
    LoadingContext * loadingContext)
{
    PlatformPhysicsComponent * position = loadingContext->GetSystems().GetSystem<PlatformPhysicsSystem>("physics")->at(entity);
    position->GetActions().CreatePositionAction()
        ->Value(Point(object["value"]["x"].asFloat(), object["value"]["y"].asFloat()))
        ->Tween(object["tween"].asFloat())
        ->Duration(object["duration"].asFloat());
    return position;
}

void * factories::PlatformerVelocityActionInflate(
    const Json::Value & object,
    const Entity & entity,
    LoadingContext * loadingContext)
{    
    PlatformPhysicsComponent * position = loadingContext->GetSystems().GetSystem<PlatformPhysicsSystem>("physics")->at(entity);
    position->GetActions().CreateVelocityAction()
        ->Value(Point(object["value"]["x"].asFloat(), object["value"]["y"].asFloat()))
        ->Tween(object["tween"].asFloat())
        ->Duration(object["duration"].asFloat());
    return position;
}
