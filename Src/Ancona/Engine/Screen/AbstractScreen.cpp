#include <Ancona/Engine/Screen/AbstractScreen.hpp>

using namespace ild;

AbstractScreen::AbstractScreen(ScreenManager & manager)
{
    this._manager = manager;
}
