#include <fstream>

#include <Ancona/System/FileOperations.hpp>
#include <Ancona/System/Log.hpp>

#import <Foundation/Foundation.h>

using namespace ild;

std::unique_ptr<std::istream> FileOperations::GetInputFileStream(const std::string & desiredFile)
{
    auto fullFile = FileOperations::ResourceRoot() + desiredFile;
    ILD_Log(fullFile);
    return std::unique_ptr<std::istream>(new std::ifstream(fullFile, std::ifstream::binary));
}

std::unique_ptr<std::ofstream> FileOperations::GetOutputFileStream(const std::string & desiredFile)
{
    auto fullFile = FileOperations::ResourceRoot() + desiredFile;
    return std::unique_ptr<std::ofstream> { new std::ofstream(fullFile, std::ofstream::out) };
}

bool FileOperations::IsFile(const std::string & filePath)
{
    auto fullFile = FileOperations::ResourceRoot() + desiredFile;
    std::ifstream fileStream(fullFile.c_str());
    return fileStream.good();
}

std::string FileOperations::ResourceRoot() 
{
    NSBundle *bundle = [NSBundle mainBundle];
    NSString *objcResourceDir = [bundle resourcePath];
    const char *cStrResourceDir = [objcResourceDir fileSystemRepresentation];
    return std::string(cStrResourceDir) + "/";
}
