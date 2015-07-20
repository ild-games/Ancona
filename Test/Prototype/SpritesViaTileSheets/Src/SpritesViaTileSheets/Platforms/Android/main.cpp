#include <Ancona/Framework/Config/Config.hpp>

#include "../../SpriteTilesheetLib/Core/SpriteTilesheetGame.hpp"
#include "../../SpriteTilesheetLib/Core/AndroidPlatform.hpp"

using namespace ild;

int main(int argc, const char *argv[])
{
    PolymorphicRegistration::RegisterType<SpriteDrawable>("ild::SpriteDrawable");
    PolymorphicRegistration::RegisterType<AnimatedDrawable>("ild::AnimatedDrawable");
    PolymorphicRegistration::RegisterType<TiledImage>("ild::TiledImage");
    PolymorphicRegistration::RegisterType<SoloImage>("ild::SoloImage");

    Config::Load("Config.txt");

    SpriteTilesheetGame game(800, 600, new AndroidPlatform());
    game.Run();
    
    return 0;
}
