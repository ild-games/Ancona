#ifndef Ancona_Engine_Audio_Jukebox_H_
#define Ancona_Engine_Audio_Jukebox_H_

#include <string>

#include <SFML/Audio.hpp>

namespace ild
{

class Jukebox
{
    public:
        static void Play(const std::string & musicKey);
        static void Play();
        static void Stop();
        static void Pause();

        /* getters and setters */
        static void musicVolumePercent(float volume);
        static float musicVolumePercent();
        static void soundVolumePercent(float volume);
        static float soundVolumePercent();

    private:
        static std::unique_ptr<sf::Music> _music;
        static std::string _musicKeyPlaying;
        static float _musicVolumePercent;
        static float _soundVolumePercent;
};

}


#endif
