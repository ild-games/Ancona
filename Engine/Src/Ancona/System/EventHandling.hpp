#ifndef Ancona_Systems_EventHandling_H_
#define Ancona_Systems_EventHandling_H_

#include <Ancona/HAL/Window.hpp>
#include <Ancona/HAL/Event.hpp>

namespace ild
{

class EventHandling
{
    public:
        static void HandleEvent(const ildhal::Event & event, bool & windowIsActive, ildhal::Window & window);
};

}

#endif
