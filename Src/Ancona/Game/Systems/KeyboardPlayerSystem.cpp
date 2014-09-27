#include <Ancona/Engine/EntityFramework/UpdateStep.hpp>
#include <Ancona/Game/Systems/KeyboardPlayerSystem.hpp>

using namespace ild;

KeyboardPlayerSystem::KeyboardPlayerSystem(SystemManager & manager, PositionSystem & positionSystem)
    : UnorderedSystem(manager, UpdateStep::Update), _positionSystem(positionSystem)
{
}

void KeyboardPlayerSystem::Update(float delta)
{
    for(auto component : *this)
    {
        component.second->Update();
    }
}

KeyboardPlayerComponent * KeyboardPlayerSystem::CreateComponent(const Entity & entity)
{
    auto posComp = _positionSystem[entity];
    Assert(posComp != NULL, "Keyboard can only control player with a position component");
    auto comp = new KeyboardPlayerComponent(*posComp);
    AttachComponent(entity, comp);
    return comp;
}
