#include <cmath>
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
    SetVolume(Jukebox::soundVolumePercent());
    Jukebox::RegisterSound(_soundKey);
}

void Sound::SetVolume(float volumePercent) {
    if (volumePercent == 0.0f) {
        _volume = 0.0f;
    } else {
        _volume = std::pow(100.0f, volumePercent - 1);
    }
}

void Sound::Play() {
    _jukeboxJobID = Jukebox::ReserveSoundLifecycleID(_soundKey);
    Jukebox::PlaySound(_soundKey, _jukeboxJobID, _volume);
}

void Sound::Stop() {
    // todo implement
}

void Sound::Pause() {
    // todo implement
}

/* getters and setters */
void Sound::pitch(float newPitch) 
{
    _pitch = newPitch;
}
