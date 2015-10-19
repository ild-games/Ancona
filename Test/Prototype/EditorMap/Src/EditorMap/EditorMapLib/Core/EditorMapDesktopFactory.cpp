#include "EditorMapDesktopFactory.hpp"

using namespace ild;

GameKeyboard * EditorMapDesktopFactory::inputHandler()
{
    return new GameKeyboard();
}
