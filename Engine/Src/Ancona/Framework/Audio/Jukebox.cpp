#include <sstream>

#include <Ancona/Framework/Audio/Jukebox.hpp>
#include <Ancona/Framework/Resource/ResourceLibrary.hpp>
#include <Ancona/System/Log.hpp>

using namespace ild;

std::string Jukebox::_musicKeyPlaying = "";
std::unique_ptr<sf::Music> Jukebox::_music = std::unique_ptr<sf::Music>(new sf::Music());
float Jukebox::_musicVolumePercent = 1.0f;
float Jukebox::_soundVolumePercent = 1.0f;

void Jukebox::Play(const std::string & musicKey) {
    if (musicKey == _musicKeyPlaying) {
        return;
    }

    _musicKeyPlaying = musicKey;
    auto resourceRoot = ResourceLibrary::ResourceRoot();
    std::stringstream stream;
    stream << resourceRoot << "/" << musicKey << ".ogg";
    _music->openFromFile(stream.str());
    _music->play();
}

void Jukebox::Play() {
    _music->setLoop(true);
    _music->play();
}

void Jukebox::Stop() {
    _musicKeyPlaying = "";
    _music->stop();
    _music.reset();
}

void Jukebox::Pause() {
    _music->pause();
}

/* getters and setters */
void Jukebox::musicVolumePercent(float volume) {
    _musicVolumePercent = volume;
    if (volume == 0.0f) {
        _music->setVolume(0.0f);
    } else {
        auto realVolume = std::pow(100.0f, volume - 1);
        _music->setVolume(realVolume * 100);
    }
}

float Jukebox::musicVolumePercent() {
    return _musicVolumePercent;
}

void Jukebox::soundVolumePercent(float volume) {
    _soundVolumePercent = volume;
}

float Jukebox::soundVolumePercent() {
    return _soundVolumePercent;
}
