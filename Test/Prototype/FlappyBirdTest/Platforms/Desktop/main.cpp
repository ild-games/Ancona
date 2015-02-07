#include <Ancona/Engine/Config/Config.hpp>
#include "Core/FlappyGame.hpp" 

#include <sstream>
#include <cstring>

#include <SFML/System.hpp>

#include "DesktopFactory.hpp"


using namespace ild;

int main(int argc, char ** argv)
{
    Config::Load("Config.txt");
    FlappyGame game(270, 480, "Flappy Bird", new DesktopFactory());
    game.Run();
}
