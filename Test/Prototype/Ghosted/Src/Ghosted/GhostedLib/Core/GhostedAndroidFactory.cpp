#include "GhostedAndroidFactory.hpp"

using namespace ild;

GameTouch * GhostedAndroidFactory::inputHandler()
{
    return new GameTouch();
}
