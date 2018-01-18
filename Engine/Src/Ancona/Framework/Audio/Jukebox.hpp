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

    private:
        static std::unique_ptr<sf::Music> _music;
        static std::string _musicKeyPlaying;
};

}


#endif
