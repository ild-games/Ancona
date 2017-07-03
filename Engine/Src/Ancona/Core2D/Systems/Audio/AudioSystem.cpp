#include <Ancona/Core2D/Systems/Audio/AudioSystem.hpp>
#include <SFML/Audio.hpp>

using namespace ild;

void AudioComponent::Serialize(Archive &arc)
{
    arc(_sounds, "sounds");
    for (auto sound: _sounds) {
        _hashedSounds.insert({sound->key(), sound});
    }
}

void AudioComponent::FetchDependencies(const Entity & entity) 
{

}

AudioSystem::AudioSystem(
        std::string name,
        SystemManager &manager) :
    UnorderedSystem(name, manager, UpdateStep::Update) {
}

void AudioSystem::Update(float delta)
{

}

AudioComponent * AudioSystem::CreateComponent(const Entity &entity) {
    AudioComponent * comp = new AudioComponent();
    AttachComponent(entity, comp);
    return comp;
}