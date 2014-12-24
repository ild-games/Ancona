#include <Ancona/Engine/Config/Config.hpp>
#include "Core/AnconaGame.hpp"

using namespace ild;

int main(int argc, char ** argv)
{
    Config::Load("Config.txt");
    AnconaGame game(1600, 1200, "Camera and Map Test");
    game.Run();
}
