#include <Ancona/Core2D/Systems/Drawable/SoloImage.hpp>
#include <Ancona/Core2D/Systems/Drawable/TiledImage.hpp>
#include <Ancona/Framework/Config/Config.hpp>

#include "../../GhostedLib/Core/GhostedGame.hpp"
#include "../../GhostedLib/Core/GhostedDesktopFactory.hpp"

using namespace ild;

int main(int argc, const char *argv[])
{
    PolymorphicRegistration::RegisterType<SpriteDrawable>("ild::SpriteDrawable");
    PolymorphicRegistration::RegisterType<ShapeDrawable>("ild::ShapeDrawable");
    PolymorphicRegistration::RegisterType<SoloImage>("ild::SoloImage");
    PolymorphicRegistration::RegisterType<TiledImage>("ild::TiledImage");
    PolymorphicRegistration::RegisterType<sf::RectangleShape>("sf::RectangleShape");

    Config::Load(*FileOperations::GetInputFileStream("Config.txt"));

    GhostedGame game(1920, 1080, new GhostedDesktopFactory());
    game.Run();
    
    return 0;
}
