#include <Ancona/Engine/Config/Config.hpp>
#include "Core/FlappyGame.hpp"

using namespace ild;

int main(int argc, char ** argv)
{
    Config::Load("Config.txt");
    FlappyGame game(270, 480, "Flappy Bird");
    game.Run();
}
