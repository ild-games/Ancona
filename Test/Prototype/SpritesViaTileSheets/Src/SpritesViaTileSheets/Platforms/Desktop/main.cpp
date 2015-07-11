#include <Ancona/Framework/Config/Config.hpp>

#include "../../SpriteTilesheetLib/Core/SpriteTilesheetGame.hpp"
#include "../../SpriteTilesheetLib/Core/DesktopPlatform.hpp"

using namespace ild;

int main(int argc, const char *argv[])
{
    PolymorphicRegistration::RegisterType<SpriteDrawable>("ild::SpriteDrawable");

    Config::Load("Config.txt");

    SpriteTilesheetGame game(800, 600, new DesktopPlatform());
    game.Run();
    
    return 0;
}
