#include "DesktopFactory.hpp"

using namespace ild;

FlappyKeyboard * DesktopFactory::GetInputHandler(ScreenManager & screenManager)
{
    return new FlappyKeyboard(screenManager); 
}
