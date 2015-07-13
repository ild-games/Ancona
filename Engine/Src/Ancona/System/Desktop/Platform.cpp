#include <fstream>

#include <Ancona/System/Platform.hpp>

using namespace ild;

std::unique_ptr<std::istream> Platform::GetInputFileStream(const std::string & desiredFile)
{
    return std::unique_ptr<std::istream>(new std::ifstream(desiredFile, std::ifstream::binary));
}
