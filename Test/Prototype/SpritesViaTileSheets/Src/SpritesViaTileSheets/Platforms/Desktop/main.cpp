#include <Ancona/Framework/Config/Config.hpp>

#include "../../SpriteTilesheetLib/Core/SpriteTilesheetGame.hpp"
#include "../../SpriteTilesheetLib/Core/DesktopPlatform.hpp"

#include "SoloImageDrawable.hpp"
#include "TiledImageDrawable.hpp"

using namespace ild;

int main(int argc, const char *argv[])
{
    PolymorphicRegistration::RegisterType<SpriteDrawable>("ild::SpriteDrawable");
    PolymorphicRegistration::RegisterType<AnimatedDrawable>("ild::AnimatedDrawable");
    PolymorphicRegistration::RegisterType<TiledImageDrawable>("ild::TileImageDrawable");
    PolymorphicRegistration::RegisterType<SoloImageDrawable>("ild::SoloImageDrawable");

    Config::Load("Config.txt");

    SpriteTilesheetGame game(800, 600, new DesktopPlatform());
    game.Run();
    
    return 0;
}
