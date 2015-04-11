#include <Ancona/Engine/Config/Config.hpp>
#include <Core/JumpyGame.hpp>
#include <Ancona/Engine/Loading/PolymorphicRegistration.hpp>
#include <Ancona/Engine/Core/Systems/Drawable/AnimatedDrawable.hpp>
#include <Ancona/Engine/Core/Systems/Drawable/ShapeDrawable.hpp>
#include <Ancona/Engine/Core/Systems/Drawable/TextDrawable.hpp>

using namespace ild;

int main(int argc, const char *argv[])
{
    PolymorphicRegistration::RegisterType<sf::RectangleShape>("sf::RectangleShape");
    PolymorphicRegistration::RegisterType<AnimatedDrawable>("ild::AnimatedDrawable");
    PolymorphicRegistration::RegisterType<TextDrawable>("ild::TextDrawable");
    PolymorphicRegistration::RegisterType<ShapeDrawable>("ild::ShapeDrawable");
    PolymorphicRegistration::RegisterType<SpriteDrawable>("ild::SpriteDrawable");

    Config::Load("Config.txt");

    JumpyGame game(400,800);
    game.Run();
    
    return 0;
}
