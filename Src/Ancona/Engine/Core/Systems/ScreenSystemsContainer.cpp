#include <Ancona/Engine/Core/Systems/ScreenSystemsContainer.hpp>

using namespace ild;

ScreenSystemsContainer::ScreenSystemsContainer(ScreenManager & screenManager) :
    _systemManager(new SystemManager()),
    _screenManager(screenManager)
{
}
