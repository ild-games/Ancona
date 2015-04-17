#include <Ancona/Engine/Config/Config.hpp>
#include <Ancona/Engine/Core/Systems/Drawable/AnimatedDrawable.hpp>
#include <Ancona/Engine/Core/Systems/Drawable/ShapeDrawable.hpp>
#include <Ancona/Engine/Core/Systems/Drawable/TextDrawable.hpp>
#include <Ancona/Game/Core/AnconaGame.hpp>

using namespace ild;

int main(int argc, char ** argv)
{
    PolymorphicRegistration::RegisterType<sf::RectangleShape>("sf::RectangleShape");
    PolymorphicRegistration::RegisterType<AnimatedDrawable>("ild::AnimatedDrawable");
    PolymorphicRegistration::RegisterType<TextDrawable>("ild::TextDrawable");
    PolymorphicRegistration::RegisterType<ShapeDrawable>("ild::ShapeDrawable");
    PolymorphicRegistration::RegisterType<SpriteDrawable>("ild::SpriteDrawable");
    Config::Load("Config.txt"); 
    AnconaGame game(800, 600, "Ancona Game");
    game.Run();
}
