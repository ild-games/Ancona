#ifndef Ancona_Core2D_Systems_Audio_Music_H_
#define Ancona_Core2D_Systems_Audio_Music_H_

#include <string>

#include <Ancona/Framework/Serializing/Serializing.hpp>

namespace ild
{

class Music
{
  public:
    Music()
    {
    }

    void Play();
    void Stop();
    void Pause();
    void Update(float delta);

    void Serialize(Archive &arc);
    void FetchDependencies(const Entity &entity);

    /* getters and setters */
    const std::string &key()
    {
        return _musicKey;
    }

  private:
    float _volume;
    std::string _musicKey;
    float _loopStart = 0.0f;
    bool _loop = true;
};

} // namespace ild

#endif
