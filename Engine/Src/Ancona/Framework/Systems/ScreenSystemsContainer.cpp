#include <Ancona/Framework/Systems/ScreenSystemsContainer.hpp>

using namespace ild;

ScreenSystemsContainer::ScreenSystemsContainer(
        ScreenManager & screenManager,
        int profile) :
    _systemManager(new SystemManager()),
    _screenManager(screenManager),
    _profile(profile)
{
}

std::vector<AbstractSystem *> ScreenSystemsContainer::GetAllSystems()
{
    std::vector<AbstractSystem *> systems;
    for (auto iterator = _systemMap.begin(); iterator != _systemMap.end(); iterator++)
    {
        systems.push_back(iterator->second);
    }
    return systems;
}