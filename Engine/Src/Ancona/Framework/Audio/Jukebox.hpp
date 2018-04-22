#ifndef Ancona_Engine_Audio_Jukebox_H_
#define Ancona_Engine_Audio_Jukebox_H_

#include <memory>
#include <string>
#include <unordered_map>

#include <SFML/Audio.hpp>

#include "JukeboxSounds.hpp"

namespace ild {

class Jukebox {
public:
    /* music */
    static void InitMusic(sf::Music* music);
    static void PlayMusic(const std::string& musicKey);
    static void PlayMusic();
    static void StopMusic();
    static void PauseMusic();

    /* sound */
    static void RegisterSound(const std::string& soundKey);
    static void ClearSounds();
    static unsigned long ReserveSoundLifecycleID(const std::string& soundKey);
    static void PlaySound(const std::string& soundKey, const unsigned long& jobID, const float& volume);

    /* getters and setters */
    static void musicVolumePercent(float volume);
    static float musicVolumePercent();
    static void soundVolumePercent(float volume);
    static float soundVolumePercent();

private:
    static std::unordered_map<std::string, std::unique_ptr<JukeboxSounds>> _jukeboxSounds;
    static sf::Music* _music;
    static std::string _musicKeyPlaying;
    static float _musicVolumePercent;
    static float _soundVolumePercent;
    static unsigned long _nextSoundLifecycleJobID;

    static void ApplyMusicVolume();
};
}

#endif
