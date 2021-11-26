#include <Ancona/System/EventHandling.hpp>
#include <Ancona/Framework/Audio/Jukebox.hpp>

using namespace ild;

void EventHandling::HandleEvent(const ildhal::Event & event, bool & windowIsActive, ildhal::Window & window)
{
    if (event.type == ildhal::Event::LostFocus) 
    {
        Jukebox::PauseMusic();
    }
    if (event.type == ildhal::Event::GainedFocus) 
    {
        Jukebox::PlayMusic(Jukebox::loop(), Jukebox::loopStart());
    }
}
