#include <fstream>

#include <Ancona/System/FileOperations.hpp>
#include <Ancona/System/Log.hpp>

using namespace ild;

std::unique_ptr<std::istream> FileOperations::GetInputFileStream(const std::string & desiredFile)
{
    return std::unique_ptr<std::istream>(new std::ifstream(desiredFile, std::ifstream::binary));
}

std::unique_ptr<std::ofstream> FileOperations::GetOutputFileStream(const std::string & desiredFile)
{
    return std::unique_ptr<std::ofstream> { new std::ofstream(desiredFile, std::ofstream::out) };
}

bool FileOperations::IsFile(const std::string & filePath)
{
    std::ifstream fileStream(desiredFile.c_str());
    return fileStream.good();
}