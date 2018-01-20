#include <Ancona/Core2D/Systems/Audio/Sound.hpp>
#include <Ancona/Framework/Audio/Jukebox.hpp>

using namespace ild;

void Sound::Serialize(Archive & arc) 
{
    arc(_soundKey, "soundKey");
    arc(_pitch, "pitch");
}

void Sound::Update(float delta) 
{
    if (_sound != nullptr && _sound->getStatus() == sf::SoundSource::Status::Stopped) {
        delete _sound;
        _sound = nullptr;
    }
}

void Sound::FetchDependencies(const Entity & entity) 
{
    SetupSound();
}

void Sound::SetupSound() 
{
    SetVolume(Jukebox::soundVolumePercent());
}

void Sound::SetVolume(float volumePercent) {
    if (volumePercent == 0.0f) {
        _volume = 0.0f;
    } else {
        _volume = std::pow(100.0f, volumePercent - 1);
    }
}

void Sound::Play() {
    auto buffer = ResourceLibrary::Get<sf::SoundBuffer>(_soundKey);
    _sound = new sf::Sound(*buffer);
    _sound->setVolume(_volume * 100.0f);
    _sound->setPitch(_pitch);
    _sound->play();
}

void Sound::Stop() {
    _sound->stop();
}

void Sound::Pause() {
    _sound->pause();
}

/* getters and setters */
void Sound::pitch(float newPitch) 
{
    _pitch = newPitch;
}
