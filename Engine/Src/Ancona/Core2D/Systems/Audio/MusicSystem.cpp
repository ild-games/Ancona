#include "MusicSystem.hpp"

#include <Ancona/Framework/Audio/Jukebox.hpp>

using namespace ild;

/* Component */
void MusicComponent::Update(float delta) {
    for (auto & music : _musics) {
        music->Update(delta);
    }
}

void MusicComponent::Serialize(Archive & arc) {
    arc(_musics, "musics");
    for (auto & music : _musics) {
        _hashedMusics.insert({music->key(), music});
    }
}

void MusicComponent::FetchDependencies(const Entity &entity) {
    for (auto & music : _musics) {
        music->FetchDependencies(entity);
    }
}

std::shared_ptr<Music> MusicComponent::GetMusic(const std::string & key) {
    return _hashedMusics[key];
}

std::shared_ptr<Music> MusicComponent::GetFirstMusic() {
    if (_musics.size() > 0) {
        return _musics[0];
    }
    
    return nullptr;
}

const std::vector<std::shared_ptr<Music>> & MusicComponent::GetAllMusics() {
    return _musics;
}

bool MusicComponent::HasMusic(const std::string & key) {
    return _hashedMusics.find(key) != _hashedMusics.end();
}

/* System */
MusicSystem::MusicSystem(
        std::string name,
        SystemManager &manager) :
    UnorderedSystem(name, manager, UpdateStep::Update) {
}

void MusicSystem::Update(float delta) {
    for (EntityComponentPair comp : *this) {
        comp.second->Update(delta);
    }
}

MusicComponent * MusicSystem::CreateComponent(const Entity &entity) {
    MusicComponent * comp = new MusicComponent();
    AttachComponent(entity, comp);
    return comp;
}

void MusicSystem::PlayMusic(const std::string & musicToPlay) {
    for (EntityComponentPair comp : *this) {
        if (comp.second->HasMusic(musicToPlay)) {
            comp.second->GetMusic(musicToPlay)->Play();
        }
    }
}

void MusicSystem::PauseAllMusic() {
    for (EntityComponentPair comp : *this) {
        for (auto & music : comp.second->GetAllMusics()) {
            music->Pause();
        }
    }
}
