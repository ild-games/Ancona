#include <Ancona/Core2D/Systems/Drawable/SoloImage.hpp>
#include <Ancona/Core2D/Systems/Drawable/ShapeDrawable.hpp>
#include <Ancona/Framework/Config/Config.hpp>
#include <Ancona/Core2D/Systems/Drawable/TiledImage.hpp>

#include "../../RotationLib/Core/RotationGame.hpp"
#include "../../RotationLib/Core/RotationDesktopFactory.hpp"

using namespace ild;

int main(int argc, const char *argv[])
{
    PolymorphicRegistration::RegisterType<SpriteDrawable>("ild::SpriteDrawable");
    PolymorphicRegistration::RegisterType<ShapeDrawable>("ild::ShapeDrawable");
    PolymorphicRegistration::RegisterType<SoloImage>("ild::SoloImage");
    PolymorphicRegistration::RegisterType<TiledImage>("ild::TiledImage");
    PolymorphicRegistration::RegisterType<sf::RectangleShape>("sf::RectangleShape");
    PolymorphicRegistration::RegisterType<TextDrawable>("ild::TextDrawable");
    PolymorphicRegistration::RegisterType<AnimatedDrawable>("ild::AnimatedDrawable");

    Config::Load(*FileOperations::GetInputFileStream("Config.txt"));

    RotationGame game(800, 600, new RotationDesktopFactory());
    game.Run();
    
    return 0;
}
