#ifndef ImpossibleDuck_Core_ImpossibleGame_hpp
#define ImpossibleDuck_Core_ImpossibleGame_hpp

#include <Ancona/Core2D/Core/Game.hpp>
#include "PlatformBase.hpp"

namespace ild
{

class ImpossibleGame : public Game
{
    public:
        ImpossibleGame(
                int width,
                int height,
                PlatformBase * platform);

    protected:
        void CreateInitialScreen();

    private:
        PlatformBase * _platform;
};

}
#endif
