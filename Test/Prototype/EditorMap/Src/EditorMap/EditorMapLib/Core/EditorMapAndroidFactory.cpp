#include "EditorMapAndroidFactory.hpp"

using namespace ild;

GameTouch * EditorMapAndroidFactory::inputHandler()
{
    return new GameTouch();
}
