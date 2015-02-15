#ifndef JumpyDuck_Core_JumpyGame_hpp
#define JumpyDuck_Core_JumpyGame_hpp

#include <Ancona/Engine/Core/Game.hpp>

namespace ild
{

class JumpyGame : public Game
{
    public:
        JumpyGame(int width, int height);

    protected:
        void CreateInitialScreen();
};

}
#endif