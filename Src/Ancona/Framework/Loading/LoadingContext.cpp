#include <Ancona/Framework/Loading/LoadingContext.hpp>
#include <Ancona/Framework/EntityFramework/SystemManager.hpp>

using namespace ild;

LoadingContext::LoadingContext(ScreenSystemsContainer & systems) :
    _systems(systems)
{
}