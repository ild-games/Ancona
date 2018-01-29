#ifndef Ancona_Systems_EventHandling_H_
#define Ancona_Systems_EventHandling_H_

#include <SFML/Window.hpp>

namespace ild
{

class EventHandling
{
    public:
        static void HandleEvent(const sf::Event & event);
};

}

#endif
