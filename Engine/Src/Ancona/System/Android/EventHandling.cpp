#include <Ancona/System/EventHandling.hpp>
#include <Ancona/Framework/Audio/Jukebox.hpp>

using namespace ild;

void EventHandling::HandleEvent(const ildhal::Event & event, bool & windowIsActive, ildhal::Window & window)
{
    if (event.type == ildhal::Event::MouseLeft)
    {
        Jukebox::PauseMusic();
        windowIsActive = false;
        window.setActive(false);
    }
    if (event.type == ildhal::Event::MouseEntered)
    {
        Jukebox::PlayMusic(Jukebox::loop(), Jukebox::loopStart());
    }
}
