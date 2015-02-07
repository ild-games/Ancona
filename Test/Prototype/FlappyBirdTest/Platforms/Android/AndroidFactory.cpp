#include "AndroidFactory.hpp"

using namespace ild;

FlappyTouch * AndroidFactory::GetInputHandler(ScreenManager & screenManager)
{
    return new FlappyTouch(screenManager); 
}
