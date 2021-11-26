#ifndef Ancona_HAL_SFML_WindowImpl_H_
#define Ancona_HAL_SFML_WindowImpl_H_

#include <SFML/Graphics.hpp>

#include <Ancona/HAL/Window.hpp>
#include <Ancona/HAL/Event.hpp>

namespace ildhal
{

class Window::Impl
{
    public:
        Impl(
            const std::string& title,
            int width,
            int height,
            unsigned int style = WindowStyle::Default);

        std::unique_ptr<sf::RenderWindow> SFMLWindow;

        void translateEventFromSFML(Event & event, sf::Event & sfmlEvent);
};

}

#endif
