#ifndef Ancona_HAL_SFML_WindowImpl_H_
#define Ancona_HAL_SFML_WindowImpl_H_

#include <SFML/Graphics.hpp>

#include <Ancona/HAL/Window.hpp>
#include <Ancona/HAL/Event.hpp>
#include <Ancona/HAL/SFML/RenderTargetImpl.hpp>

namespace ildhal
{

namespace priv
{

class WindowImpl : public RenderTargetImpl
{
    public:
        WindowImpl(
            const std::string & title,
            int width,
            int height,
            unsigned int style = WindowStyle::Default);

        /* getters and setters */
        sf::RenderWindow & getSfmlRenderWindow() const { return static_cast<sf::RenderWindow &>(*_sfmlRenderTarget); }

};

}

}

#endif
