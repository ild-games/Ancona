#include <sstream>

#include <Ancona/Framework/Audio/Jukebox.hpp>
#include <Ancona/Framework/Resource/ResourceLibrary.hpp>
#include <Ancona/System/Log.hpp>
#include <Ancona/Util/Assert.hpp>

using namespace ild;

std::unordered_map<std::string, std::unique_ptr<JukeboxSounds>> Jukebox::_jukeboxSounds = std::unordered_map<std::string, std::unique_ptr<JukeboxSounds>>();
std::string Jukebox::_musicKeyPlaying = "";
float Jukebox::_musicVolumePercent = 1.0f;
float Jukebox::_soundVolumePercent = 1.0f;
sf::Music* Jukebox::_music = nullptr;
float Jukebox::_loopStart = 0.0f;
unsigned long Jukebox::_nextSoundLifecycleJobID = 0;

void Jukebox::Update()
{
    if (_music != nullptr) {
        // do our own looping of music since the SFML setLoopPoints API is inconsisent in whether or not it works
        if (_music->getStatus() == sf::SoundSource::Status::Stopped) {
            _music->play();
            _music->setPlayingOffset(sf::seconds(_loopStart));
        }
    }
}

void Jukebox::InitMusic(sf::Music* music)
{
    _music = music;
}

void Jukebox::RegisterSound(const std::string& soundKey)
{
    if (_jukeboxSounds.find(soundKey) == _jukeboxSounds.end()) {
        _jukeboxSounds.emplace(soundKey, std::unique_ptr<JukeboxSounds>(new JukeboxSounds()));
    }

    _jukeboxSounds[soundKey]->Add(soundKey);
}

void Jukebox::ClearSounds()
{
    _jukeboxSounds.clear();
    _nextSoundLifecycleJobID = 0;
}

unsigned long Jukebox::ReserveSoundLifecycleID(const std::string& soundKey)
{
    if (_jukeboxSounds.find(soundKey) == _jukeboxSounds.end()) {
        ILD_Assert(true, "Sound key has not been registered in the Jukebox, please call Jukebox::RegisterSound before reserving a sound allocation.");
    }

    _nextSoundLifecycleJobID++;
    _jukeboxSounds[soundKey]->CreateJob(_nextSoundLifecycleJobID);
    return _nextSoundLifecycleJobID;
}

void Jukebox::PlaySound(const std::string& soundKey, const unsigned long& jobID, const float& volume)
{
    if (_jukeboxSounds.find(soundKey) == _jukeboxSounds.end()) {
        ILD_Assert(true, "Sound key has not been registered in the Jukebox, please call Jukebox::RegisterSound before playing a sound");
    }

    _jukeboxSounds[soundKey]->Play(jobID, volume);
}

void Jukebox::PlayMusic(const std::string& musicKey, const float& loopStart)
{
    if (!_music) {
        return;
    }

    if (musicKey == _musicKeyPlaying) {
        return;
    }

    _musicKeyPlaying = musicKey;
    auto resourceRoot = ResourceLibrary::ResourceRoot();
    std::stringstream stream;
    stream << resourceRoot << "/" << musicKey << ".ogg";
    _music->openFromFile(stream.str());
    PlayMusic(loopStart);
}

void Jukebox::PlayMusic(const float& loopStart)
{
    if (!_music) {
        return;
    }

    ApplyMusicVolume();
    if (loopStart >= 0.0f) {
        _loopStart = loopStart;
    }
    _music->play();
}

void Jukebox::StopMusic()
{
    if (!_music) {
        return;
    }

    _musicKeyPlaying = "";
    _music->stop();
}

void Jukebox::PauseMusic()
{
    if (!_music) {
        return;
    }

    _music->pause();
}

void Jukebox::ApplyMusicVolume()
{
    if (!_music) {
        return;
    }

    if (_musicVolumePercent == 0.0f) {
        _music->setVolume(0.0f);
    } else {
        auto realVolume = std::pow(100.0f, _musicVolumePercent - 1);
        _music->setVolume(realVolume * 100);
    }
}

/* getters and setters */
void Jukebox::musicVolumePercent(float volume)
{
    _musicVolumePercent = volume;
    ApplyMusicVolume();
}

float Jukebox::musicVolumePercent()
{
    return _musicVolumePercent;
}

void Jukebox::soundVolumePercent(float volume)
{
    _soundVolumePercent = volume;
}

float Jukebox::soundVolumePercent()
{
    return _soundVolumePercent;
}

float Jukebox::loopStart()
{
    return _loopStart;
}
