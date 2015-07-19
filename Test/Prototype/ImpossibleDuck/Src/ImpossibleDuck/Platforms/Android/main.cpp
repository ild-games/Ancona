#include <Ancona/Core2D/Systems/Drawable/AnimatedDrawable.hpp>
#include <Ancona/Core2D/Systems/Drawable/TextDrawable.hpp>
#include <Ancona/Core2D/Systems/Drawable/ShapeDrawable.hpp>
#include <Ancona/Framework/Config/Config.hpp>
#include <Ancona/Framework/Serializing/PolymorphicRegistration.hpp>
#include <Ancona/System/Android/AndroidPlatform.hpp>
#include <Ancona/System/Platform.hpp>

#include <ImpossibleDuck/ImpossibleLib/Core/ImpossibleGame.hpp>
#include <ImpossibleDuck/ImpossibleLib/Core/ImpossibleAndroidFactory.hpp>

using namespace ild;

int main(int argc, const char *argv[])
{
    PolymorphicRegistration::RegisterType<sf::RectangleShape>("sf::RectangleShape");
    PolymorphicRegistration::RegisterType<AnimatedDrawable>("ild::AnimatedDrawable");
    PolymorphicRegistration::RegisterType<TextDrawable>("ild::TextDrawable");
    PolymorphicRegistration::RegisterType<ShapeDrawable>("ild::ShapeDrawable");
    PolymorphicRegistration::RegisterType<SpriteDrawable>("ild::SpriteDrawable");

    ANativeActivity * activity = (ANativeActivity *) argv;
    AndroidPlatform::internalPath(std::string(activity->internalDataPath));
    AndroidPlatform::assetManager(activity->assetManager);

    Config::Load(*Platform::GetInputFileStream("Config.txt"));

    ImpossibleGame game(1920, 1080, new ImpossibleAndroidFactory());
    game.Run();
    
    return 0;
}
