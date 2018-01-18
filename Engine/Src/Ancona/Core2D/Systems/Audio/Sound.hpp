#ifndef Ancona_Core2D_Systems_Audio_Sound_H_
#define Ancona_Core2D_Systems_Audio_Sound_H_

#include <string>

#include <SFML/Audio.hpp>

#include <Ancona/Framework/Serializing/Serializing.hpp>

namespace ild
{

typedef float modulationFunction();

class Sound
{
    public:
        Sound() {}

        void Play();
        void Stop();

        const std::string & key() { return _soundKey; }

        void Serialize(Archive &arc);
        void FetchDependencies(const Entity & entity);

    private:
        float _volume;
        std::string _soundKey;
        std::unique_ptr<sf::Sound> _sound;

};

}

#endif
