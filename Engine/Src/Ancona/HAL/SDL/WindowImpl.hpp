#ifndef Ancona_HAL_SDL_WindowImpl_H_
#define Ancona_HAL_SDL_WindowImpl_H_

#include <Ancona/HAL/Window.hpp>

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

    private:
};

}

#endif
