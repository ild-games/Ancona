#include "GhostedDesktopFactory.hpp"

using namespace ild;

GameKeyboard * GhostedDesktopFactory::inputHandler()
{
    return new GameKeyboard();
}
