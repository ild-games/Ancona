#include <Ancona/Engine/Screens/AbstractScreen.hpp>
#include <Ancona/Engine/Screens/LoadingScreen.hpp>

using namespace ild;

AbstractScreen::AbstractScreen(ScreenManager & manager)
    : _manager(manager)
{
    __Initialized = false;
}
