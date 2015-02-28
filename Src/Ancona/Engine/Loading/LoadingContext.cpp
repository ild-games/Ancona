#include <Ancona/Engine/Loading/LoadingContext.hpp>

using namespace ild;

LoadingContext::LoadingContext(SystemManager & systems)
{
    auto namedComponentInflaters = systems.GetComponentInflaters();
    for(auto & namedComponentPair : namedComponentInflaters)
    {
        _inflaterMap.AddAbstract(namedComponentPair.first, namedComponentPair.second);
    }
}
