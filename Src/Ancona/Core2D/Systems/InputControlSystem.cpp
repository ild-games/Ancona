#include <Ancona/Core2D/Systems/InputControlSystem.hpp>

using namespace ild;

InputControlSystem::InputControlSystem(SystemManager & manager)
    : UnorderedSystem<InputControlComponent>(manager, UpdateStepEnum::Input)
{

}

void InputControlSystem::Update(float delta)
{
    for(EntityComponentPair componentPair : *this)
    {
        componentPair.second->Update(delta);
    }
}

void InputControlSystem::AddComponent(const Entity & entity,
        InputControlComponent * component)
{
    AttachComponent(entity, component);
}
