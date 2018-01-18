#include <sstream>

#include <Ancona/Core2D/Systems/Audio/Music.hpp>
#include <Ancona/Framework/Audio/Jukebox.hpp>

using namespace ild;

void Music::Serialize(Archive & arc) {
    arc(_volume, "volume");
    arc(_musicKey, "musicKey");
}

void Music::FetchDependencies(const Entity & entity) {
}

void Music::Play() {
    Jukebox::Play(_musicKey);
}

void Music::Stop() {
    Jukebox::Stop();
}
