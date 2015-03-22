#include <Ancona/Engine/Loading/SaverContext.hpp>
#include <Ancona/Engine/EntityFramework/SystemManager.hpp>

using namespace ild;

SaverContext::SaverContext(ScreenSystemsContainer & systems) :
    _systems(systems)
{
    auto namedComponentSavers = systems.GetSystemManager().GetComponentSavers();
    for(auto & namedComponentPair : namedComponentSavers)
    {
        _saverMap.AddAbstract(namedComponentPair.first, namedComponentPair.second);
    }
}
