#include "ImpossibleDesktopFactory.hpp"

using namespace ild;

ImpossibleKeyboard * ImpossibleDesktopFactory::inputHandler()
{
    return new ImpossibleKeyboard();
}
