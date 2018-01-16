#include <sstream>

#include <Ancona/Framework/Audio/Jukebox.hpp>
#include <Ancona/Framework/Resource/ResourceLibrary.hpp>

using namespace ild;

std::string Jukebox::_musicKeyPlaying = "";
std::unique_ptr<sf::Music> Jukebox::_music = std::unique_ptr<sf::Music>(new sf::Music());

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
    _music->play();
}

void Jukebox::Stop() {
    _musicKeyPlaying = "";
    _music->stop();
}

void Jukebox::Pause() {
    _music->pause();
}
