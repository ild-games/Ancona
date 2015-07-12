#include <Ancona/Framework/Config/Config.hpp>

#include "../../SpriteTilesheetLib/Core/SpriteTilesheetGame.hpp"
#include "../../SpriteTilesheetLib/Core/DesktopPlatform.hpp"

#include <Ancona/Core2D/Systems/Drawable/SoloImage.hpp>
#include <Ancona/Core2D/Systems/Drawable/TiledImage.hpp>

using namespace ild;

int main(int argc, const char *argv[])
{
    PolymorphicRegistration::RegisterType<SpriteDrawable>("ild::SpriteDrawable");
    PolymorphicRegistration::RegisterType<TiledImage>("ild::TiledImage");
    PolymorphicRegistration::RegisterType<SoloImage>("ild::SoloImage");

    Config::Load("Config.txt");

    SpriteTilesheetGame game(800, 600, new DesktopPlatform());
    game.Run();
    
    return 0;
}
