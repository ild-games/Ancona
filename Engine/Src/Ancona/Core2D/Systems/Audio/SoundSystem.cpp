#include <Ancona/Core2D/Systems/Audio/SoundSystem.hpp>
#include <SFML/Audio.hpp>

using namespace ild;

void SoundComponent::Serialize(Archive &arc)
{
    arc(_sounds, "sounds");
    for (auto sound: _sounds) {
        _hashedSounds.insert({sound->key(), sound});
    }
}

void SoundComponent::FetchDependencies(const Entity & entity) 
{
    for (auto sound : _sounds) {
        sound->FetchDependencies(entity);
    }
}

SoundSystem::SoundSystem(
        std::string name,
        SystemManager &manager) :
    UnorderedSystem(name, manager, UpdateStep::Update) {
}

void SoundSystem::Update(float delta)
{

}

SoundComponent * SoundSystem::CreateComponent(const Entity &entity) {
    SoundComponent * comp = new SoundComponent();
    AttachComponent(entity, comp);
    return comp;
}