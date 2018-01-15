#include "MusicSystem.hpp"

using namespace ild;

/* Component */
void MusicComponent::Update(float delta)
{
}

void MusicComponent::Serialize(Archive & arc)
{
    arc(_musics, "musics");
    for (auto & music : _musics) {
        _hashedMusics.insert({music->key(), music});
    }
}

void MusicComponent::FetchDependencies(const Entity &entity)
{
    for (auto & music : _musics) {
        music->FetchDependencies(entity);
    }
}

/* System */
MusicSystem::MusicSystem(
        std::string name,
        SystemManager &manager) :
    UnorderedSystem(name, manager, UpdateStep::Update)
{
}

void MusicSystem::Update(float delta)
{
    for (EntityComponentPair comp : *this)
    {
        comp.second->Update(delta);
    }
}

MusicComponent * MusicSystem::CreateComponent(const Entity &entity)
{
    MusicComponent * comp = new MusicComponent();
    AttachComponent(entity, comp);
    return comp;
}
