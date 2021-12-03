#include "AutoStartMusicSystem.hpp"

using namespace ild;

/* Component */
void AutoStartMusicComponent::Update(float delta)
{
}

void AutoStartMusicComponent::Serialize(Archive &arc)
{
    arc(_musicKeyToPlay, "musicKeyToPlay");
    arc.system(_musicSystem, "music");
}

void AutoStartMusicComponent::FetchDependencies(const Entity &entity)
{
    _musicSystem->PlayMusic(_musicKeyToPlay);
}

/* System */
AutoStartMusicSystem::AutoStartMusicSystem(std::string name, SystemManager &manager)
    : UnorderedSystem(name, manager, UpdateStep::Update)
{
}

void AutoStartMusicSystem::Update(float delta)
{
    for (EntityComponentPair comp : *this)
    {
        comp.second->Update(delta);
    }
}

AutoStartMusicComponent *AutoStartMusicSystem::CreateComponent(const Entity &entity)
{
    AutoStartMusicComponent *comp = new AutoStartMusicComponent();
    AttachComponent(entity, comp);
    return comp;
}
