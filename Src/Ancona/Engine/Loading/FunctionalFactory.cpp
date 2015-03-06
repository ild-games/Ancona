#include <Ancona/Engine/Loading/FunctionalFactory.hpp>

using namespace ild;

void * factories::RectangleInflate(
        const Json::Value & object,
        const Entity entity,
        LoadingContext * loadingContext)
{
    return new sf::RectangleShape(
            sf::Vector2f(
                object["width"].asFloat(),
                object["height"].asFloat()));
}

void * factories::CircleInflate(
        const Json::Value & object,
        const Entity entity,
        LoadingContext * loadingContext)
{
    return new sf::CircleShape(object["radius"].asFloat());
}
