#include <Ancona/System/EventHandling.hpp>
#include <Ancona/Framework/Audio/Jukebox.hpp>

using namespace ild;

void EventHandling::HandleEvent(const sf::Event & event)
{
    if (event.type == sf::Event::MouseLeft)
    {
        Jukebox::PauseMusic();
    }
    if (event.type == sf::Event::MouseEntered)
    {
        Jukebox::PlayMusic(Jukebox::loop(), Jukebox::loopStart());
    }
}
