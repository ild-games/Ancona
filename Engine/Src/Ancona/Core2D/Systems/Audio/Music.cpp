#include <sstream>

#include <Ancona/Core2D/Systems/Audio/Music.hpp>
#include <Ancona/Framework/Resource/ResourceLibrary.hpp>

using namespace ild;

void Music::Serialize(Archive & arc) 
{
    arc(_volume, "volume");
    arc(_musicKey, "musicKey");
}

void Music::FetchDependencies(const Entity & entity) 
{
    auto resourceRoot = ResourceLibrary::ResourceRoot();
    std::stringstream stream;
    stream << resourceRoot << "/" << _musicKey << ".ogg";
    _music = std::unique_ptr<sf::Music>(new sf::Music());
    _music->openFromFile(stream.str());
}

void Music::Play() {
    _music->play();
}

void Music::Stop() {
    _music->stop();
}
