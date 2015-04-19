#include <Ancona/Framework/Config/Config.hpp>
#include "Core/FlappyGame.hpp"

#include <sstream>
#include <cstring>

#include <android/asset_manager.h>
#include <android/log.h>
#include <android/native_activity.h>
#include <android/window.h>

#include <SFML/System.hpp>
#include "AndroidFactory.hpp"

using namespace ild;

int main(int argc, char ** argv)
{

    AAssetManager * mgr = (AAssetManager *) argv;
    const char* dirname = "";
    AAssetDir* assetDir = AAssetManager_openDir(mgr, dirname);
    const char* filename = (const char*)NULL;
    std::ostringstream fileStream;

    while ((filename = AAssetDir_getNextFileName(assetDir)) != NULL) 
    {
        AAsset* asset = AAssetManager_open(mgr, filename, AASSET_MODE_STREAMING);
        char buf[BUFSIZ + 1];
        memset(buf,0, (BUFSIZ + 1 ) * sizeof(char));

        if(strcmp("Config.txt",filename))
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

    std::istringstream configStream(fileStream.str());

    AAssetDir_close(assetDir);


    Config::Load(configStream);
    FlappyGame game(270, 480, "Flappy Bird", new AndroidFactory());
    game.Run();
}
