#include <Ancona/Core2D/Systems/Audio/SoundSystem.hpp>
#include <SFML/Audio.hpp>

using namespace ild;

void SoundComponent::Update(float delta) {
}

void SoundComponent::Serialize(Archive &arc) {
    arc(_sounds, "sounds");
    for (auto & sound: _sounds) {
        _hashedSounds.insert({sound->key(), sound});
    }
}

void SoundComponent::FetchDependencies(const Entity & entity) {
    for (auto & sound : _sounds) {
        sound->FetchDependencies(entity);
    }
}

std::shared_ptr<Sound> SoundComponent::GetSound(const std::string & key) { 
    return _hashedSounds[key]; 
}

void SoundComponent::SetVolume(float volumePercent) {
    for (auto & sound : _sounds) {
        sound->SetVolume(volumePercent);
    }
}

SoundSystem::SoundSystem(
        std::string name,
        SystemManager &manager) :
    UnorderedSystem(name, manager, UpdateStep::Update) {
}

void SoundSystem::Update(float delta) {
    for (EntityComponentPair comp : *this) {
        comp.second->Update(delta);
    }
}

SoundComponent * SoundSystem::CreateComponent(const Entity &entity) {
    SoundComponent * comp = new SoundComponent();
    AttachComponent(entity, comp);
    return comp;
}


void SoundSystem::SetVolume(float volumePercent) {
    for (EntityComponentPair comp : *this) {
        comp.second->SetVolume(volumePercent);
    }
}
