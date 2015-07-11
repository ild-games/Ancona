#include "DesktopPlatform.hpp"

using namespace ild;

GameKeyboard * DesktopPlatform::inputHandler()
{
    return new GameKeyboard();
}
