#ifndef Ancona_Engine_Core_Systems_ScreenSystemsContainer_H_
#define Ancona_Engine_Core_Systems_ScreenSystemsContainer_H_

#include <map>
#include <string>

#include <SFML/Graphics.hpp>
#include <Ancona/Engine/EntityFramework/SystemManager.hpp>

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
         * @param manager The system manager that belongs to the screen.
         */
        ScreenSystemsContainer();
            

        /**
         * @brief Constructs a system for the screen. Registers it with the system map.
         *
         * @tparam T Type of system being constructed.
         * @param systemName Name of the system.
         * @param sysArgs Rest of parameters to construct the system after the name.
         *
         * @return Pointer to the system.
         */
        template <typename T, typename... Args>
        T * ConstructSystem(std::string systemName, Args&&... sysArgs)
        {
            T * system = new T(systemName, std::forward<Args>(sysArgs)...);
            _systemMap[systemName] = system;
            return system;
        }

        template <typename T>
        T * GetSystem(std::string systemName)
        {
            return static_cast<T *>(_systemMap[systemName]);
        }

        /* getters and setters */
        SystemManager & GetManager() { return *_systemManager; }
    protected:
        /**
         * @brief Map used to store the system references. It is not recommended you use this to get the systems during gameplay, only for loading.
         */
        std::map<std::string, AbstractSystem *> _systemMap;
        /**
         * @brief Manages all the entity systems on the screen.
         */
        SystemManager * _systemManager;
};

}

#endif
