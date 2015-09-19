#include "RotationAndroidFactory.hpp"

using namespace ild;

GameTouch * RotationAndroidFactory::inputHandler()
{
    return new GameTouch();
}
