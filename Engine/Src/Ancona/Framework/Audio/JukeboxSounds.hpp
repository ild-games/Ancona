#ifndef Ancona_Engine_Audio_JukeboxSounds_H_
#define Ancona_Engine_Audio_JukeboxSounds_H_

#include <memory>
#include <string>
#include <vector>

#include <Ancona/HAL.hpp>

namespace ild
{

class JukeboxSounds
{
  public:
    JukeboxSounds();

    void Add(const std::string &soundKey);
    void CreateJob(const unsigned long &jobID);
    void Play(const unsigned long &jobID, const float &volume);

  private:
    static const int NUM_ALLOCATED_SOUNDS = 5;

    int _numRegisteredSounds = 0;
    int _nextSoundToUse = 0;
    std::vector<std::unique_ptr<ildhal::Sound>> _sounds;
    unsigned long _jobIDs[NUM_ALLOCATED_SOUNDS];

    int FindSoundIndexByJob(const unsigned long &jobID);
};

} // namespace ild

#endif
