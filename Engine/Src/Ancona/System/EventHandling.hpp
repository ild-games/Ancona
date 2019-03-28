#ifndef Ancona_Systems_EventHandling_H_
#define Ancona_Systems_EventHandling_H_

#include <SFML/Graphics.hpp>

namespace ild
{

class EventHandling
{
    public:
        static void HandleEvent(const sf::Event & event, bool & windowIsActive, sf::RenderWindow & window);
};

}

#endif
