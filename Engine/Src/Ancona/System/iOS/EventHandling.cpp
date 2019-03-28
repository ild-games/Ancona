#include <Ancona/System/EventHandling.hpp>
#include <Ancona/Framework/Audio/Jukebox.hpp>
#include <SFML/Graphics.hpp>

using namespace ild;

void EventHandling::HandleEvent(const sf::Event & event, bool & windowIsActive, sf::RenderWindow & window)
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
