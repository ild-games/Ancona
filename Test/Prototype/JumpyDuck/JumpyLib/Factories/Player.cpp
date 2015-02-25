#include "Player.hpp"

using namespace ild;

Entity JumpyPlayer::Create(JumpyGameSystems *gameSystems)
{
    auto entity = gameSystems->GetManager().CreateEntity();
    auto physicsComponent = gameSystems->GetPhysics().CreateComponent(entity);

    //Set up input
    auto inputHandler = new JumpyKeyboard();
    auto controlComponent = new JumpyInputComponent(entity, *physicsComponent, *inputHandler);
    gameSystems->GetInput().AddComponent(entity, controlComponent);

    auto drawable = new SpriteDrawable(*physicsComponent,"flappy",0,0,Point());
    auto drawableComponent = gameSystems->GetDrawable().CreateComponent(entity);
    drawableComponent->AddDrawable("sprite", drawable);

    auto size = drawable->GetSize();
    auto collisionComponent = gameSystems
        ->GetCollision()
        .CreateComponent(entity,sf::Vector3f(size.x,size.y,0), 0,BodyType::Solid);

    return entity;
}

