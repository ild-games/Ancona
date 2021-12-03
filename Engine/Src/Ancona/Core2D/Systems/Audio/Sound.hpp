#ifndef Ancona_Core2D_Systems_Audio_Sound_H_
#define Ancona_Core2D_Systems_Audio_Sound_H_

#include <string>

#include <Ancona/Framework/Serializing/Serializing.hpp>

namespace ild
{

typedef float modulationFunction();

class Sound
{
  public:
    Sound()
    {
    }

    Sound(std::string key, float pitch = 1.0f) : _soundKey(key), _pitch(pitch)
    {
    }

    void Play();
    void Stop();
    void Pause();
    void SetVolume(float volumePercent);

    void Serialize(Archive &arc);
    void FetchDependencies(const Entity &entity);
    void SetupSound();

    /* getters and setters */
    const std::string &key()
    {
        return _soundKey;
    }
    float pitch()
    {
        return _pitch;
    }
    void pitch(float newPitch);

  private:
    std::string _soundKey;
    float _pitch = 1.0f;
    float _volume = 1.0f;
    unsigned long _jukeboxJobID = 0;
};

} // namespace ild

#endif
