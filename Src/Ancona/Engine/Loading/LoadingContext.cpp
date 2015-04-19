#include <Ancona/Engine/Loading/LoadingContext.hpp>
#include <Ancona/Engine/EntityFramework/SystemManager.hpp>

using namespace ild;

LoadingContext::LoadingContext(ScreenSystemsContainer & systems) :
    _systems(systems)
{
}