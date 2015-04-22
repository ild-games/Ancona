#include "DesktopPlatform.hpp"

using namespace ild;

ImpossibleKeyboard * DesktopPlatform::inputHandler()
{
    return new ImpossibleKeyboard();
}