#include <fstream>

#include <Ancona/System/FileOperations.hpp>
#include <Ancona/System/iOS/iOSFileOperations.hpp>
#include <Ancona/System/Log.hpp>

#import <Foundation/Foundation.h>

using namespace ild;

std::unique_ptr<std::istream> FileOperations::GetInputFileStream(const std::string & desiredFile)
{
    if (iOSFileOperations::IsFileInDocumentsFolder(desiredFile))
    {
        auto fileInDocuments = iOSFileOperations::DocumentsRoot() + desiredFile;
        ILD_Log("In documents: " + fileInDocuments);
        return std::unique_ptr<std::istream>(new std::ifstream(fileInDocuments, std::ifstream::binary));
    }

    auto fileInAppBundle = FileOperations::ResourceRoot() + desiredFile;
    ILD_Log("In app bundle: " + fileInAppBundle);
    return std::unique_ptr<std::istream>(new std::ifstream(fileInAppBundle, std::ifstream::binary));
}

std::unique_ptr<std::ofstream> FileOperations::GetOutputFileStream(const std::string & desiredFile)
{
    auto fullFile = iOSFileOperations::DocumentsRoot() + desiredFile;
    ILD_Log("Writing to file: " + fullFile);
    return std::unique_ptr<std::ofstream> { new std::ofstream(fullFile, std::ofstream::out) };
}

bool FileOperations::IsFile(const std::string & filePath)
{
    auto fullFile = FileOperations::ResourceRoot() + filePath;
    std::ifstream fileStream(fullFile.c_str());
    return fileStream.good();
}

std::string _resourceRoot = "";
std::string FileOperations::ResourceRoot() 
{
    if (_resourceRoot != "") 
    {
        return _resourceRoot;
    }

    NSBundle *bundle = [NSBundle mainBundle];
    NSString *objcResourceDir = [bundle resourcePath];
    const char *cStrResourceDir = [objcResourceDir fileSystemRepresentation];
    _resourceRoot = std::string(cStrResourceDir) + "/";
    return _resourceRoot;
}

std::string iOSFileOperations::DocumentsRoot() 
{
    NSArray *searchPaths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory,
                       NSUserDomainMask, YES);
    NSString *documentsPath = [searchPaths objectAtIndex:0];
    std::string resPath( [ documentsPath UTF8String ] ) ;
    return resPath + "/";
}

bool iOSFileOperations::IsFileInDocumentsFolder(const std::string & filePath)
{
    auto documentsFullFile = iOSFileOperations::DocumentsRoot() + filePath;
    std::ifstream documentsFileStream(documentsFullFile.c_str());
    return documentsFileStream.good();
}
