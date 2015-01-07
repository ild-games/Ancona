#include <Ancona/Engine/Config/Config.hpp>
#include "Core/FlappyGame.hpp"

#include <sstream>
#include <cstring>

#include <android/asset_manager.h>
#include <android/log.h>
#include <android/native_activity.h>
#include <android/window.h>

#include <SFML/System.hpp>


using namespace ild;

int main(int argc, char ** argv)
{

    __android_log_print(ANDROID_LOG_INFO, "AnconaTag", "Start Flappy");
    AAssetManager * mgr = (AAssetManager *) argv;
    __android_log_print(ANDROID_LOG_INFO, "AnconaTag", "Into Flappy 1 %p", mgr);
    const char* dirname = "";
    AAssetDir* assetDir = AAssetManager_openDir(mgr, dirname);
    __android_log_print(ANDROID_LOG_INFO, "AnconaTag", "Into Flappy 2");
    const char* filename = (const char*)NULL;
    std::ostringstream fileStream;

    while ((filename = AAssetDir_getNextFileName(assetDir)) != NULL) 
    {
        AAsset* asset = AAssetManager_open(mgr, filename, AASSET_MODE_STREAMING);
        char buf[BUFSIZ + 1];
        memset(buf,0, (BUFSIZ + 1 ) * sizeof(char));

        __android_log_print(ANDROID_LOG_INFO, "AnconaTag", "Current file %s", filename);
        if(strcmp("Config.txt",filename))
        {
            __android_log_print(ANDROID_LOG_INFO, "AnconaTag", "Skipping file %s", filename);
            continue;
        }
        else
        {
            __android_log_print(ANDROID_LOG_INFO, "AnconaTag", "Config.txt found!");
        }


        int nb_read = 0;
        //FILE* out = fopen(filename, "w");
        __android_log_print(ANDROID_LOG_INFO, "AnconaTag", "Current file 2 %s", filename);
        while ((nb_read = AAsset_read(asset, buf, BUFSIZ)) > 0)
        {
            __android_log_print(ANDROID_LOG_INFO, "AnconaTag", "writing %d", nb_read);
            //fwrite(buf, nb_read, 1, out);
            fileStream << buf;
            
            memset(buf,0, (BUFSIZ + 1 ) * sizeof(char));
        }
        __android_log_print(ANDROID_LOG_INFO, "AnconaTag", "Current file 3 %s", filename);
        //fclose(out);
        __android_log_print(ANDROID_LOG_INFO, "AnconaTag", "Current file 4 %s", filename);
        AAsset_close(asset);
        __android_log_print(ANDROID_LOG_INFO, "AnconaTag", "Leaving the loop");

        break;
    }

    std::istringstream configStream(fileStream.str());

    __android_log_print(ANDROID_LOG_INFO, "AnconaTag", "Current file 6 %s", filename);
    AAssetDir_close(assetDir);


    Config::Load(configStream);
    FlappyGame game(270, 480, "Flappy Bird");
    game.Run();
}
