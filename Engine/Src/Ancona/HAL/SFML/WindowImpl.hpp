#ifndef Ancona_HAL_SFML_WindowImpl_H_
#define Ancona_HAL_SFML_WindowImpl_H_

#include <SFML/Graphics.hpp>

#include <Ancona/HAL/Window.hpp>

namespace ild
{

class WindowImpl
{
    public:
        WindowImpl(
            const std::string& title,
            int width,
            int height,
            unsigned int style = WindowStyle::Default);

    private:
        sf::RenderWindow _sfmlWindow;
};

}

#endif
