#include "ImpossibleAndroidFactory.hpp"

using namespace ild;

ImpossibleTouch * ImpossibleAndroidFactory::inputHandler()
{
    return new ImpossibleTouch();
}
