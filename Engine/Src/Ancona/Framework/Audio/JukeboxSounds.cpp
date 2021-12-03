#include <Ancona/Framework/Audio/JukeboxSounds.hpp>
#include <Ancona/Framework/Resource/ResourceLibrary.hpp>
#include <Ancona/System/Log.hpp>

using namespace ild;

JukeboxSounds::JukeboxSounds()
{
    for (int i = 0; i < NUM_ALLOCATED_SOUNDS; i++)
    {
        _jobIDs[i] == 0;
    }
}

void JukeboxSounds::Add(const std::string &soundKey)
{
    _numRegisteredSounds++;
    if (_sounds.size() == NUM_ALLOCATED_SOUNDS)
    {
        return;
    }

    _sounds.emplace_back(new ildhal::Sound(*ResourceLibrary::Get<ildhal::SoundBuffer>(soundKey)));
}

void JukeboxSounds::CreateJob(const unsigned long &jobID)
{
    _jobIDs[_nextSoundToUse] = jobID;
    _nextSoundToUse++;
    if (_nextSoundToUse == _sounds.size())
    {
        _nextSoundToUse = 0;
    }
}

void JukeboxSounds::Play(const unsigned long &jobID, const float &volume)
{
    int indexToUse = FindSoundIndexByJob(jobID);
    if (indexToUse == -1)
    {
        return;
    }

    _sounds[indexToUse]->volume(volume * 100.0f);
    _sounds[indexToUse]->Stop();
    _sounds[indexToUse]->Play();
}

int JukeboxSounds::FindSoundIndexByJob(const unsigned long &jobID)
{
    for (int i = 0; i < NUM_ALLOCATED_SOUNDS; i++)
    {
        if (_jobIDs[i] == jobID)
        {
            return i;
        }
    }
    return -1;
}
