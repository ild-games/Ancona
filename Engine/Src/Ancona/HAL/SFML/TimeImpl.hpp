#ifndef Ancona_HAL_SFML_TimeImpl_H_
#define Ancona_HAL_SFML_TimeImpl_H_

#include <SFML/System.hpp>

#include <Ancona/HAL/Time.hpp>

namespace ildhal
{

namespace priv
{

class TimeImpl
{
    public:
        TimeImpl();
        TimeImpl(float seconds);

        /* getters and setters */
        sf::Time & sfmlTime() const { return *_sfmlTime; }

    private:
        std::unique_ptr<sf::Time> _sfmlTime;
};

}

}

#endif
