#include <string>

#include <Ancona/Framework/Serializing/Serializing.hpp>

namespace ild
{

typedef float modulationFunction();

class Sound
{
public:
    void Play();
    void Stop();

    std::string key() { return _soundKey; }

    void Serialize(Archive &arc);
private:

    bool _loopSound;
    float _volume;
    std::string _soundKey;

};
}