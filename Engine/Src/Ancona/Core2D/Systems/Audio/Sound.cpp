#include <Ancona/Core2D/Systems/Audio/Sound.hpp>

using namespace ild;

void Sound::Serialize(Archive & arc) 
{
    arc(_volume, "volume");
    arc(_soundKey, "soundKey");
}

void Sound::FetchDependencies(const Entity & entity) 
{
    auto buffer = ResourceLibrary::Get<sf::SoundBuffer>(_soundKey);
    _sound = std::unique_ptr<sf::Sound>(new sf::Sound(*buffer));
}

void Sound::Play() {
    _sound->play();
}

void Sound::Stop() {
    _sound->stop();
}
