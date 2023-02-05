#include <sstream>
#include <sys/stat.h>

#include <Ancona/System/Android/AndroidFileOperations.hpp>
#include <Ancona/System/FileOperations.hpp>
#include <Ancona/System/Log.hpp>
#include <Ancona/Util/Assert.hpp>

namespace ild
{

AAssetManager * AndroidFileOperations::_assetManager = nullptr;
std::string AndroidFileOperations::_internalPath = "";

bool IsFileInNonApkStorage(const std::string & filePath)
{
    struct stat sb;
    int32_t res = stat(filePath.c_str(), &sb);
    return res == 0 && sb.st_mode & S_IFREG;
}

std::unique_ptr<std::istream> FileOperations::GetInputFileStream(const std::string & desiredFile)
{
    std::unique_ptr<std::istream> returnStream;
    returnStream.reset(AndroidFileOperations::GetAndroidFileInputStream(desiredFile));
    return returnStream;
}

std::unique_ptr<std::ofstream> FileOperations::GetOutputFileStream(const std::string & desiredFile)
{
    std::string fullFileName = AndroidFileOperations::internalPath() + "/" + desiredFile;

    CreateDirectory(GetDirName(fullFileName));

    std::unique_ptr<std::ofstream> returnStream { new std::ofstream(fullFileName, std::ofstream::out) };

    ILD_Assert(returnStream->is_open(), "Failed to open " + desiredFile);

    return returnStream;
}

std::string FileOperations::GetDirName(const std::string & filePath)
{
    return filePath.substr(0, filePath.find_last_of("/"));
}

bool FileOperations::CreateDirectory(const std::string & dirPath)
{
    if (!IsDir(dirPath))
    {
        CreateDirectory(GetDirName(dirPath));
        mkdir(dirPath.c_str(), 0770);
        return true;
    }
    return false;
}

bool FileOperations::IsDir(const std::string & dirPath)
{
    struct stat sb;
    int32_t res = stat(dirPath.c_str(), &sb);
    return res == 0 && sb.st_mode & S_IFDIR;
}

bool FileOperations::IsFile(const std::string & filePath)
{
    std::string fullInternalPath = AndroidFileOperations::internalPath() + "/" + filePath;
    if (IsFileInNonApkStorage(fullInternalPath))
    {
        return true;
    }

    return !!AndroidFileOperations::OpenFile(fullInternalPath);
}

std::istream * AndroidFileOperations::GetAndroidFileInputStream(const std::string & desiredFile)
{
    std::string fullInternalPath = _internalPath + "/" + desiredFile;
    if (IsFileInNonApkStorage(fullInternalPath))
    {
        return new std::ifstream(fullInternalPath, std::ifstream::binary);
    }
    else
    {
        auto apkFileStream = OpenFile(desiredFile);
        ILD_Assert(
            apkFileStream != nullptr,
            "Could not find the " + desiredFile + " file in app storage or within apk.");
        return new std::istringstream(apkFileStream->str());
    }
}

std::unique_ptr<std::ostringstream> AndroidFileOperations::OpenFile(const std::string & desiredFile)
{
    MakeFilesDir();

    const int BUFFER_SIZE = 255;
    char buf[BUFFER_SIZE + 1];
    std::unique_ptr<std::ostringstream> fileStream { new std::ostringstream() };

    AAsset * assetFile = AAssetManager_open(_assetManager, desiredFile.c_str(), AASSET_MODE_BUFFER);
    if (!assetFile)
    {
        return nullptr;
    }

    int nb_read = 0;
    memset(buf, 0, (BUFFER_SIZE + 1) * sizeof(char));
    while ((nb_read = AAsset_read(assetFile, buf, BUFFER_SIZE)) > 0)
    {
        (*fileStream) << buf;

        memset(buf, 0, (BUFFER_SIZE + 1) * sizeof(char));
    }
    AAsset_close(assetFile);

    return fileStream;
}

bool AndroidFileOperations::FilesDirPresent()
{
    return FileOperations::IsDir(_internalPath);
}

void AndroidFileOperations::MakeFilesDir()
{
    FileOperations::CreateDirectory(_internalPath);
}

std::string FileOperations::ResourceRoot()
{
    return "";
}

} // namespace ild
