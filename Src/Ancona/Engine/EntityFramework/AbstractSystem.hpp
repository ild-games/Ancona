#ifndef Ancona_Engine_EntityFramework_AbstractSystem_H_
#define Ancona_Engine_EntityFramework_AbstractSystem_H_

#include <memory>
#include <string>

#include <Ancona/Engine/EntityFramework/Entity.hpp>
#include <Ancona/Engine/EntityFramework/UpdateStep.hpp>
#include <Ancona/Engine/Loading/Archive.hpp>
#include <Ancona/Util/Assert.hpp>

namespace ild 
{

class SystemManager;

/**
 * @brief Class that all systems must indirectly inherit from. It is used to hide the 
 *  component type of the system from the system manager.
 *
 * @owner Jeff Swenson
 */
class AbstractSystem 
{
    public:
        /**
         * @brief Create and initialzies the system.  The system will register
         *  itself with SystemManager.
         *
         * @param systemManager SystemManager that the system belongs to.
         * @param updateStep The step that the system needs to be updated during.
         * @param systemName The unique name of the system.
         */
        AbstractSystem(
                std::string systemName,
                SystemManager & systemManager,
                UpdateStepEnum updateStep);

        /**
         * @brief Called to update all components controlled by the system.
         *
         * @param delta The amount of time that has passed since the last update in ms
         */
        virtual void Update(float delta) = 0;

        /**
         * @brief Remove any component managed by the system that is attached to the entity.
         *  The system will notify the systemManager that the component was removed.
         *
         * @param entity Entity that should have its component removed
         */
        virtual void RemoveComponent(const Entity & entity) = 0;

        /**
         * @brief Remove any component managed by the system that is attached to the entity.  
         *  The system will NOT notify the systemManager that the component was removed.  This 
         *  should only be used when the entity is being deleted by SystemManager.
         *
         * @param entity Entity that is being deleted
         */
        virtual void EntityIsDeleted(const Entity & entity) = 0;
        
        /**
         * @brief Default serialize for a system, should never be reached.
         */
        virtual void Serialize(Archive & arc) 
        {
            Assert(false, "No serializer implemented for this system.");
        }

        /**
         * @brief Used to collect the dependent components for the component made by this system.
         *        This is called after the component is initialized, but can also be used whenever 
         *        the location of its dependencies in memory may have changed.
         *
         * @param entity Entity the component is associated with.
         */
        virtual void FetchComponentDependencies(const Entity & entity) = 0;

    protected:
        SystemManager & _systemManager;

};

}


#endif

