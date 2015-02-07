#include <Ancona/Engine/Config/Config.hpp>
#include <Core/JumpyGame.hpp>

using namespace ild;

int main(int argc, const char *argv[])
{
    Config::Load("Config.txt");

    JumpyGame game(400,800);
    game.Run();
    
    return 0;
}
