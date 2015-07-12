#include <Ancona/Framework/Config/Config.hpp>
#include <Ancona/Core2D/Systems/Drawable/AnimatedDrawable.hpp>
#include <Ancona/Core2D/Systems/Drawable/TextDrawable.hpp>
#include <Ancona/Core2D/Systems/Drawable/ShapeDrawable.hpp>
#include <Ancona/Framework/Serializing/PolymorphicRegistration.hpp>

#include <ImpossibleDuck/ImpossibleLib/Core/ImpossibleGame.hpp>
#include <ImpossibleDuck/ImpossibleLib/Core/AndroidPlatform.hpp>


#include <sstream>
#include <cstring>

#include <android/asset_manager.h>
#include <android/log.h>
#include <android/native_activity.h>
#include <android/window.h>
using namespace ild;

int main(int argc, const char *argv[])
{
    __android_log_print(ANDROID_LOG_VERBOSE, "Ancona", "ANCONA_SFML!!: starting main");
    PolymorphicRegistration::RegisterType<sf::RectangleShape>("sf::RectangleShape");
    PolymorphicRegistration::RegisterType<AnimatedDrawable>("ild::AnimatedDrawable");
    PolymorphicRegistration::RegisterType<TextDrawable>("ild::TextDrawable");
    PolymorphicRegistration::RegisterType<ShapeDrawable>("ild::ShapeDrawable");
    PolymorphicRegistration::RegisterType<SpriteDrawable>("ild::SpriteDrawable");


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


    Config::Load("Config.txt");
    __android_log_print(ANDROID_LOG_VERBOSE, "Ancona", "ANCONA_SFML!!: Loading Config");

    ImpossibleGame game(1920, 1080, new AndroidPlatform());
    game.Run();
    
    return 0;
}
