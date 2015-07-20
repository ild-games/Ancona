#include "AndroidPlatform.hpp"

using namespace ild;

GameTouch * AndroidPlatform::inputHandler()
{
    return new GameTouch();
}
