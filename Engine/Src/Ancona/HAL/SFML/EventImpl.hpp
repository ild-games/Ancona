#ifndef Ancona_HAL_SFML_EventImpl_H_
#define Ancona_HAL_SFML_EventImpl_H_

#include <SFML/Window.hpp>

#include <Ancona/HAL/Event.hpp>

namespace ildhal
{

namespace priv
{

class EventImpl
{
    public:
        static void TranslateSFMLToAncona(const sf::Event & sfmlEvent, ildhal::Event & event);
};

}

}

#endif