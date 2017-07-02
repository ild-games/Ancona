#include <Ancona/Core2D/Systems/Audio/Sound.hpp>

#include <sstream>

#include <Ancona/System/Log.hpp>

using namespace ild;


void LogSound(std::string sound) {
    ILD_Log(sound);
}

void Sound::Serialize(Archive & arc) 
{
    arc(_loopSound, "loopSound");
    arc(_volume, "volume");
    arc(_soundKey, "soundKey");
}

void Sound::Play() {
    std::ostringstream os;
    os << "Sound key: " << _soundKey << " volume: " << _volume << " looping? " << _loopSound;
    LogSound(os.str());
}