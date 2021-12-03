#include <Ancona/Framework/Audio/Jukebox.hpp>
#include <Ancona/System/EventHandling.hpp>

using namespace ild;

void EventHandling::HandleEvent(const ildhal::Event &event, bool &windowIsActive, ildhal::Window &window)
{
    if (event.type == ildhal::Event::MouseLeft)
    {
        Jukebox::PauseMusic();
        windowIsActive = false;
        window.SetActive(false);
    }
    if (event.type == ildhal::Event::MouseEntered)
    {
        Jukebox::PlayMusic(Jukebox::loop(), Jukebox::loopStart());
    }
}
