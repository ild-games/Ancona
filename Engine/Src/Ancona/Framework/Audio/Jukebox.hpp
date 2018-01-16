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
        static void Stop();

    private:
        static std::unique_ptr<sf::Music> _music;
        static std::string _musicKeyPlaying;
};

}


#endif
