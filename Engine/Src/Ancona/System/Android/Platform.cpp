#include <sstream>
#include <sys/stat.h>

#include <Ancona/System/Platform.hpp>
#include <Ancona/System/Android/AndroidPlatform.hpp>
#include <Ancona/Util/Assert.hpp>

using namespace ild;

AAssetManager * AndroidPlatform::_assetManager = nullptr;
std::string AndroidPlatform::_internalPath = "";

std::unique_ptr<std::istream> Platform::GetInputFileStream(const std::string & desiredFile)
{
    std::unique_ptr<std::istream> returnStream;
    returnStream.reset(AndroidPlatform::GetAndroidFileInputStream(desiredFile));
    return returnStream;
}

std::unique_ptr<std::ostream> Platform::GetOutputFileStream(const std::string & desiredFile)
{
    std::unique_ptr<std::ostream> returnStream;
    returnStream.reset(dynamic_cast<std::ostream *>(AndroidPlatform::OpenFile(AndroidPlatform::internalPath() + "/" + desiredFile)));
    return returnStream;
}

std::istream * AndroidPlatform::GetAndroidFileInputStream(const std::string & desiredFile)
{
    std::ostringstream * nonApkFileStream = OpenFile(_internalPath + "/" + desiredFile);
    if (nonApkFileStream != nullptr)
    {
        return new std::istringstream(nonApkFileStream->str());
    }
    else 
    {
        std::ostringstream * apkFileStream = OpenFile(desiredFile);
        Assert(apkFileStream != nullptr, "Could not find the " + desiredFile + " file in app storage or within apk.");
        WriteApkFileToNonApkStorage(desiredFile, new std::istringstream(apkFileStream->str()));
        return new std::istringstream(apkFileStream->str());
    }
}

std::ostringstream * AndroidPlatform::OpenFile(const std::string & desiredFile)
{
    if (!FilesDirPresent())
    {
        MakeFilesDir();
    }

    const int BUFFER_SIZE=255;
    char buf[BUFFER_SIZE];
    std::ostringstream * fileStream = new std::ostringstream();

    AAsset * assetFile = AAssetManager_open(_assetManager, desiredFile.c_str(), AASSET_MODE_BUFFER);
    if(!assetFile)
    {
        return nullptr;
    }

    int nb_read = 0;
    while ((nb_read = AAsset_read(assetFile, buf, BUFFER_SIZE)) > 0)
    {
        *fileStream << buf;

        memset(buf,0, (BUFFER_SIZE + 1 ) * sizeof(char));
    }
    AAsset_close(assetFile);

    return fileStream;
}

bool AndroidPlatform::FilesDirPresent()
{
    struct stat sb;
    int32_t res = stat(_internalPath.c_str(), &sb);
    return res == 0 && sb.st_mode & S_IFDIR;
}

void AndroidPlatform::MakeFilesDir()
{
    mkdir(_internalPath.c_str(), 0770);
}

void AndroidPlatform::WriteApkFileToNonApkStorage(const std::string & filename, std::istream * streamToWrite)
{
    //TODO implement
    std::string fileFullPath = _internalPath + "/" + filename;
    std::ostringstream fileStream(fileFullPath.c_str());
    fileStream << streamToWrite->rdbuf();
}
