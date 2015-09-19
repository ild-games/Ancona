#include <Ancona/Framework/Config/Config.hpp>
#include <Ancona/Core2D/Systems/Drawable/ShapeDrawable.hpp>
#include <Ancona/Core2D/Systems/Drawable/ImageDrawable.hpp>

#include "../../GhostedLib/Core/GhostedGame.hpp"
#include "../../GhostedLib/Core/GhostedDesktopFactory.hpp"

using namespace ild;

int main(int argc, const char *argv[])
{
    PolymorphicRegistration::RegisterType<ShapeDrawable>("ild::ShapeDrawable");
    PolymorphicRegistration::RegisterType<ImageDrawable>("ild::ImageDrawable");
    PolymorphicRegistration::RegisterType<sf::RectangleShape>("sf::RectangleShape");

    Config::Load(*FileOperations::GetInputFileStream("Config.txt"));

    GhostedGame game(1920, 1080, new GhostedDesktopFactory());
    game.Run();
    
    return 0;
}
