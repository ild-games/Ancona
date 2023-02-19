#include <Ancona/HAL/OS.hpp>
#include <SDL2/SDL.h>

namespace ildhal
{

void * getNativeActivity()
{
    return nullptr;
}

const char * getInternalStoragePath()
{
    return SDL_AndroidGetInternalStoragePath();
}

} // namespace ildhal
