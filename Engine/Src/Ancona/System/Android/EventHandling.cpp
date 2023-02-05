#include <Ancona/Framework/Audio/Jukebox.hpp>
#include <Ancona/System/EventHandling.hpp>

using namespace ild;

void EventHandling::HandleEvent(const ildhal::Event & event, bool & windowIsActive, ildhal::Window & window)
{
    if (event.type == ildhal::Event::LostFocus)
    {
        Jukebox::PauseMusic();

        // TODO: this was needed in SFML, maybe not in SDL?
        // windowIsActive = false;
        // window.SetActive(false);
    }
    if (event.type == ildhal::Event::GainedFocus)
    {
        Jukebox::PlayMusic(Jukebox::loop(), Jukebox::loopStart());
    }
}
