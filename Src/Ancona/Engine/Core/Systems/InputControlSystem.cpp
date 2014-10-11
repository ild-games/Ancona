#include <Ancona/Engine/Core/Systems/InputControlSystem.hpp>

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
