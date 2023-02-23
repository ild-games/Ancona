#include <sstream>

#include <SDL2/SDL.h>

#include <Ancona/HAL/FileOps.hpp>
#include <Ancona/System/Log.hpp>
#include <Ancona/Util/Assert.hpp>

namespace ildhal
{

std::unique_ptr<std::istream> FileOps::GetInputFileStream(const std::string & filename)
{
    SDL_RWops * rwops = SDL_RWFromFile(filename.c_str(), "rb");
    if (rwops == nullptr) {
        return nullptr;
    }

    SDL_RWseek(rwops, 0, RW_SEEK_END);
    auto size = SDL_RWtell(rwops);
    SDL_RWseek(rwops, -size, RW_SEEK_END);
    auto buf = new char[size + 1];
    SDL_RWread(rwops, buf, 1, size);
    buf[size] = '\0';

    auto buf_str = std::string(buf);
    auto return_stream = std::make_unique<std::istringstream>(buf_str);

    delete buf;

    auto close_error_code = SDL_RWclose(rwops);
    ILD_Assert(close_error_code == 0, "Failed to close file!: " << filename << "\nSDL error: " << SDL_GetError());
    return return_stream;
}

void FileOps::SaveToFile(const char * data, size_t size, const std::string & filename)
{
    SDL_RWops * rwops = SDL_RWFromFile(filename.c_str(), "wb");
    if (rwops == nullptr) {
        return;
    }

    SDL_RWwrite(rwops, data, size, 1);
    SDL_RWclose(rwops);
}

} // namespace ildhal
