#ifndef Ancona_Engine_Core_Systems_ScreenSystemsContainer_H_
#define Ancona_Engine_Core_Systems_ScreenSystemsContainer_H_

#include <map>
#include <memory>
#include <string>

#include <Ancona/Framework/EntityFramework/SystemManager.hpp>
#include <Ancona/Framework/Screens/ScreenManager.hpp>
#include <Ancona/Util/Assert.hpp>

namespace ild
{

class SystemManager;
class AbstractSystem;

/**
 * @brief Holds the systems used by a screen.
 *
 * @author Jeff Swenson
 * @author Tucker Lein
 */
class ScreenSystemsContainer
{
  public:
    /**
     * @brief Constructs the container for the game's systems.
     *
     * @param screenManager The screen manager for the game.
     * @param profile The profile for this instance of the game.
     */
    ScreenSystemsContainer(ScreenManager &screenManager, int profile = -1);

    /**
     * @brief Constructs a system for the screen. Registers it with the system map.
     *
     * @tparam T Type of system being constructed.
     * @param systemName Name of the system.
     * @param sysArgs Rest of parameters to construct the system after the name.
     *
     * @return Pointer to the system.
     */
    template<typename T, typename... Args>
    T *ConstructSystem(std::string systemName, Args &&...sysArgs)
    {
        ILD_Assert(_systemMap.find(systemName) == _systemMap.end(), systemName + " already exists for this screen.");
        T *system = new T(systemName, std::forward<Args>(sysArgs)...);
        _systemMap[systemName] = system;
        return system;
    }

    /**
     * @brief Get a specific system.
     *
     * @tparam T Type of the system being returned.
     * @param systemName Name of the system.
     *
     * @return Instance of the system.
     */
    template<typename T>
    T *GetSystem(const std::string &systemName)
    {
        ILD_Assert(
            _systemMap.find(systemName) != _systemMap.end(),
            systemName + " does not exist, please construct it first.");
        return static_cast<T *>(_systemMap[systemName]);
    }

    /* getters and setters */
    SystemManager &systemManager() { return *_systemManager; }
    ScreenManager &screenManager() { return _screenManager; }
    int profile() { return _profile; }
    std::map<std::string, AbstractSystem *>::const_iterator begin() { return _systemMap.begin(); }
    std::map<std::string, AbstractSystem *>::const_iterator end() { return _systemMap.end(); }

  protected:
    /**
     * @brief Map used to store the system references. It is not recommended you use this to get the systems during
     * gameplay, only for loading.
     */
    std::map<std::string, AbstractSystem *> _systemMap;
    /**
     * @brief Manages all the entity systems on the screen.
     */
    std::unique_ptr<SystemManager> _systemManager;
    /**
     * @brief ScreenManager instance for the game.
     */
    ScreenManager &_screenManager;
    /**
     * @brief Profile used in this specific instance of the game.
     */
    int _profile;
};

} // namespace ild

#endif
