#include <Ancona/Engine/Core/Systems/ScreenSystemsContainer.hpp>

using namespace ild;

ScreenSystemsContainer::ScreenSystemsContainer(ScreenManager & screenManager) :
    _screenManager(screenManager)
{
    _systemManager = new SystemManager();
}
