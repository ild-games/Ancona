#include "AndroidPlatform.hpp"

using namespace ild;

ImpossibleTouch * AndroidPlatform::inputHandler()
{
    return new ImpossibleTouch();
}
