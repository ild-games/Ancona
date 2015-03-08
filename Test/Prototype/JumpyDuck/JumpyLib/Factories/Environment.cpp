#include "Environment.hpp"

using namespace ild;

Entity JumpyEnvironment::CreateEnvironmentBody(JumpyGameSystems * gameSystems, Point position, Point size)
{
    auto entity = gameSystems->GetSystemManager().CreateEntity();
    auto physicsComponent = gameSystems->GetPhysics().CreateComponent(entity);
    physicsComponent->GetActions().CreatePositionAction()
        ->Value(position);

    sf::RectangleShape * shape = new sf::RectangleShape(size);
    shape->setFillColor(sf::Color::Red);

    auto drawable = new ShapeDrawable(*physicsComponent, *shape, 0, 0);
    auto drawableComponent = gameSystems->GetDrawable().CreateComponent(entity);
    drawableComponent->AddDrawable("sprite", drawable);

    gameSystems
        ->GetCollision()
        .CreateComponent(entity,sf::Vector3f(size.x,size.y,0), 0,BodyType::Environment);

    return 0;
}

Entity JumpyEnvironment::CreateSolidBody(JumpyGameSystems * gameSystems)
{
    auto entity = gameSystems->GetSystemManager().CreateEntity();
    auto physicsComponent = gameSystems->GetPhysics().CreateComponent(entity);
    physicsComponent->GetActions().CreatePositionAction()
        ->Value(Point(300,50));

    sf::RectangleShape * shape = new sf::RectangleShape(sf::Vector2f(10,10));
    shape->setFillColor(sf::Color::Red);

    auto drawable = new ShapeDrawable(*physicsComponent, *shape, 0, 0);
    auto drawableComponent = gameSystems->GetDrawable().CreateComponent(entity);
    drawableComponent->AddDrawable("sprite", drawable);

    auto size = drawable->GetSize();
    gameSystems
        ->GetCollision()
        .CreateComponent(entity,sf::Vector3f(size.x,size.y,0), 0,BodyType::Solid);

    return 0;
}
