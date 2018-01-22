#include <Ancona/Framework/Resource/ResourceLibrary.hpp>
#include <Ancona/System/Log.hpp>

#include "JukeboxSounds.hpp"

using namespace ild;


JukeboxSounds::JukeboxSounds() {
    for (int i = 0; i < NUM_ALLOCATED_SOUNDS; i++) {
        _jobIDs[i] == 0;
    }
}

void JukeboxSounds::Add(const std::string & soundKey) {
    _numRegisteredSounds++;
    if (_sounds.size() == NUM_ALLOCATED_SOUNDS) {
        return;
    }

    _sounds.emplace_back(new sf::Sound(*ResourceLibrary::Get<sf::SoundBuffer>(soundKey)));
}


void JukeboxSounds::CreateJob(const unsigned long & jobID) {
    _jobIDs[_nextSoundToUse] = jobID;
    _nextSoundToUse++;
    if (_nextSoundToUse == _sounds.size()) {
        _nextSoundToUse = 0;
    }
}

void JukeboxSounds::Play(const unsigned long & jobID, const float & volume) {
    int indexToUse = FindSoundIndexByJob(jobID);
    if (indexToUse == -1) {
        return;
    }

    _sounds[indexToUse]->setVolume(volume * 100.0f);
    _sounds[indexToUse]->stop();
    _sounds[indexToUse]->play();
}

int JukeboxSounds::FindSoundIndexByJob(const unsigned long & jobID) {
    for (int i = 0; i < NUM_ALLOCATED_SOUNDS; i++) {
        if (_jobIDs[i] == jobID) {
            return i;
        }
    }
    return -1;
}
