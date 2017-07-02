#include <string>

#include <Ancona/Framework/Serializing/Serializing.hpp>

namespace ild
{

typedef float modulationFunction();

class Sound
{

  private:
    bool _loopSound;
    float _volume;

  public:
    void Play();
    void Stop();

    void Serialize(Archive &arc);
};
}