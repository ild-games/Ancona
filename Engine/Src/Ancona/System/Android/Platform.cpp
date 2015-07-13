#include <sstream>

#include <Ancona/System/Platform.hpp>
#include <Ancona/System/Android/AndroidPlatform.hpp>

using namespace ild;

AAssetManager * AndroidPlatform::_assetManager = nullptr;

std::unique_ptr<std::istream> Platform::GetInputFileStream(const std::string & desiredFile)
{
    const int BUFFER_SIZE=255;
    char buf[BUFFER_SIZE];
    AAssetManager * mgr = AndroidPlatform::assetManager();
    std::ostringstream fileStream;

    AAsset * assetFile = AAssetManager_open(mgr, desiredFile.c_str(), AASSET_MODE_BUFFER);
    if(!assetFile)
    {
        return nullptr;
    }

    int nb_read = 0;
    while ((nb_read = AAsset_read(assetFile, buf, BUFFER_SIZE)) > 0)
    {
        fileStream << buf;

        memset(buf,0, (BUFFER_SIZE + 1 ) * sizeof(char));
    }
    AAsset_close(assetFile);

    std::unique_ptr<std::istream> returnStream(new std::istringstream(fileStream.str()));


    return returnStream;
}
