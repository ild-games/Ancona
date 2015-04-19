#include <Ancona/Engine/Systems/ScreenSystemsContainer.hpp>

using namespace ild;

ScreenSystemsContainer::ScreenSystemsContainer(
        ScreenManager & screenManager,
        int profile) :
    _systemManager(new SystemManager()),
    _screenManager(screenManager),
    _profile(profile)
{
}
