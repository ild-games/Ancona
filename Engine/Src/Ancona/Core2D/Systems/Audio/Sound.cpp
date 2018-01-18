#include <Ancona/Core2D/Systems/Audio/Sound.hpp>
#include <Ancona/Framework/Audio/Jukebox.hpp>

using namespace ild;

void Sound::Serialize(Archive & arc) 
{
    arc(_soundKey, "soundKey");
    arc(_pitch, "pitch");
}

void Sound::FetchDependencies(const Entity & entity) 
{
    SetupSound();
}

void Sound::SetupSound() 
{
    auto buffer = ResourceLibrary::Get<sf::SoundBuffer>(_soundKey);
    _sound = std::unique_ptr<sf::Sound>(new sf::Sound(*buffer));
    _sound->setPitch(_pitch);
    SetVolume(Jukebox::soundVolumePercent());
}

void Sound::SetVolume(float volumePercent) {
    if (volumePercent == 0.0f) {
        _sound->setVolume(0.0f);
    } else {
        auto realVolume = std::pow(100.0f, volumePercent - 1);
        _sound->setVolume(realVolume * 100.0f);
    }
}

void Sound::Play() {
    _sound->play();
}

void Sound::Stop() {
    _sound->stop();
}

/* getters and setters */
void Sound::pitch(float newPitch) 
{
    _pitch = newPitch;
    _sound->setPitch(newPitch);
}
