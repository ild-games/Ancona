#include <sstream>

#include <Ancona/Core2D/Systems/Audio/Music.hpp>
#include <Ancona/Framework/Audio/Jukebox.hpp>

using namespace ild;

void Music::Serialize(Archive & arc) {
    arc(_volume, "volume");
    arc(_musicKey, "musicKey");
    arc(_loopStart, "loopStart");
    arc(_loop, "loop");
}

void Music::Update(float delta) {
}

void Music::FetchDependencies(const Entity & entity) {
}

void Music::Play() {
    Jukebox::PlayMusic(_musicKey, _loop, _loopStart);
}

void Music::Stop() {
    Jukebox::StopMusic();
}

void Music::Pause() {
    Jukebox::PauseMusic();
}
