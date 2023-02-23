#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <memory>

namespace ildhal
{

class FileOps
{
  public:
    static std::unique_ptr<std::istream> GetInputFileStream(const std::string & filename);

    static void SaveToFile(const char * data, size_t size, const std::string & filename);
};

} // namespace ildhal
