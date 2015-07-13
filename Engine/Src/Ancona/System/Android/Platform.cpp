#include <sstream>

#include <Ancona/System/Platform.hpp>
#include <Ancona/System/Android/AndroidPlatform.hpp>

using namespace ild;

AAssetManager * AndroidPlatform::_assetManager = nullptr;

std::unique_ptr<std::istream> Platform::GetInputFileStream(const std::string & desiredFile)
{
    AAssetManager * mgr = AndroidPlatform::assetManager();
    const char* dirname = "";
    AAssetDir* assetDir = AAssetManager_openDir(mgr, dirname);
    const char* filename = (const char*)NULL;
    std::ostringstream fileStream;

    while ((filename = AAssetDir_getNextFileName(assetDir)) != NULL) 
    {
        AAsset* asset = AAssetManager_open(mgr, filename, AASSET_MODE_STREAMING);
        char buf[BUFSIZ + 1];
        memset(buf,0, (BUFSIZ + 1 ) * sizeof(char));

        if(strcmp(desiredFile.c_str(),filename))
        {
            continue;
        }

        int nb_read = 0;
        while ((nb_read = AAsset_read(asset, buf, BUFSIZ)) > 0)
        {
            fileStream << buf;

            memset(buf,0, (BUFSIZ + 1 ) * sizeof(char));
        }
        break;
    }

    std::unique_ptr<std::istream> returnStream(new std::istringstream(fileStream.str()));

    AAssetDir_close(assetDir);

    return returnStream;
}
