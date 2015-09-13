#include <Ancona/Core2D/Systems/Drawable/SoloImage.hpp>
#include <Ancona/Framework/Config/Config.hpp>
#include <Ancona/System/Android/AndroidFileOperations.hpp>
#include <Ancona/System/FileOperations.hpp>

#include "../../RotationLib/Core/RotationGame.hpp"
#include "../../RotationLib/Core/RotationAndroidFactory.hpp"

using namespace ild;

int main(int argc, const char *argv[])
{
    PolymorphicRegistration::RegisterType<SpriteDrawable>("ild::SpriteDrawable");
    PolymorphicRegistration::RegisterType<SoloImage>("ild::SoloImage");

    ANativeActivity * activity = (ANativeActivity *) argv;
    AndroidFileOperations::internalPath(std::string(activity->internalDataPath));
    AndroidFileOperations::assetManager(activity->assetManager);

    Config::Load(*FileOperations::GetInputFileStream("Config.txt"));


    RotationGame game(800, 600, new RotationAndroidFactory());
    game.Run();
    
    return 0;
}
