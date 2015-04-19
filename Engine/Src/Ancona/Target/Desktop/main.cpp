#include <Ancona/Framework/Config/Config.hpp>
#include <Ancona/Game/Core/AnconaGame.hpp>

using namespace ild;

int main(int argc, char ** argv)
{
    Config::Load("Config.txt"); 
    AnconaGame game(800, 600, "Ancona Game");
    game.Run();
}
