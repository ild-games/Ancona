#ifndef ImpossibleDuck_Core_ImpossibleGame_hpp
#define ImpossibleDuck_Core_ImpossibleGame_hpp

#include <Ancona/Core2D/Core/Game.hpp>
#include "ImpossiblePlatformFactory.hpp"

namespace ild
{

class ImpossibleGame : public Game
{
    public:
        ImpossibleGame(
                int width,
                int height,
                ImpossiblePlatformFactory * platform);

    protected:
        void CreateInitialScreen();

    private:
        ImpossiblePlatformFactory * _platform;
};

}
#endif
