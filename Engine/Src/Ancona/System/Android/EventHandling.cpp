#include <Ancona/System/EventHandling.hpp>
#include <Ancona/Framework/Audio/Jukebox.hpp>
#include <Ancona/System/Log.hpp>
#include <SFML/Graphics.hpp>

using namespace ild;

void EventHandling::HandleEvent(const sf::Event & event, bool & windowIsActive, sf::RenderWindow & window)
{
    if (event.type == sf::Event::MouseLeft)
    {
        Jukebox::PauseMusic();
        windowIsActive = false;
        window.setActive(false);
    }
    if (event.type == sf::Event::MouseEntered)
    {
        Jukebox::PlayMusic(Jukebox::loop(), Jukebox::loopStart());
    }
}
