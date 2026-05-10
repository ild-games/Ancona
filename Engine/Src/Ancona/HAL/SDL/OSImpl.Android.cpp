#include <Ancona/HAL/OS.hpp>
#include <SDL3/SDL.h>

namespace ildhal
{

void * getNativeActivity()
{
    return nullptr;
}

const char * getInternalStoragePath()
{
    return SDL_GetAndroidInternalStoragePath();
}

} // namespace ildhal
