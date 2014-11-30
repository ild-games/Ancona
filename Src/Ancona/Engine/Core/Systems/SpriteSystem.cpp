#include <Ancona/Engine/Core/Systems/SpriteSystem.hpp>
#include <Ancona/Engine/Core/Systems/SpriteComponent.hpp>
#include <Ancona/Engine/EntityFramework/UpdateStep.hpp>

using namespace ild;

SpriteSystem::SpriteSystem(
        sf::RenderWindow & window, 
        SystemManager & systemManager, 
        PositionSystem & positionSystem)
    : UnorderedSystem(systemManager,UpdateStep::Draw), _window(window), _positionSystem(positionSystem)
{

}

SpriteComponent * SpriteSystem::CreateComponent(
        const Entity & entity, 
        const std::string & textureKey)
{
    auto positionComponent = _positionSystem[entity];

    Assert(
            positionComponent != NULL,
            "A sprite component can only be attached to an entity with a position component"
          );

    SpriteComponent * component = new SpriteComponent(*positionComponent,textureKey);

    AttachComponent(entity, component);

    return component;    
}

void SpriteSystem::Update(float delta)
{
    for(EntityComponentPair componentPair : *this)
    {
        componentPair.second->Draw(_window);
    }
}
