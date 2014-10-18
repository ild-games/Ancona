#include <Ancona/Engine/Screen/AbstractScreen.hpp>

using namespace ild;

AbstractScreen::AbstractScreen(ScreenManager & manager)
    : _manager(manager)
{
    __Initialized = false;
}
