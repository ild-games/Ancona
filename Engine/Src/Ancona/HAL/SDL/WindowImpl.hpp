#ifndef Ancona_HAL_SDL_WindowImpl_H_
#define Ancona_HAL_SDL_WindowImpl_H_

#include <Ancona/HAL/Window.hpp>

namespace ildhal
{

namespace priv
{

class WindowImpl
{
    public:
        WindowImpl(
            const std::string& title,
            int width,
            int height,
            unsigned int style = WindowStyle::Default);
};

}

}

#endif
