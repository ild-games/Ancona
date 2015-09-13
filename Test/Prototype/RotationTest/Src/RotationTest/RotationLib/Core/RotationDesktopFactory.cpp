#include "RotationDesktopFactory.hpp"

using namespace ild;

GameKeyboard * RotationDesktopFactory::inputHandler()
{
    return new GameKeyboard();
}
