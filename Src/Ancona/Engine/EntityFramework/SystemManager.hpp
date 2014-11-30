#ifndef Ancona_Engine_EntityFramework_SystemManager_H_
#define Ancona_Engine_EntityFramework_SystemManager_H_

#include <map>
#include <set>
#include <unordered_map>
#include <vector>

#include <Ancona/Engine/EntityFramework/Entity.hpp>
#include <Ancona/Engine/EntityFramework/UpdateStep.hpp>

namespace ild
{

class AbstractSystem;

/**
 * @brief Used to update entity systems and track entity state.
 *
 * @author Jeff Swenson
 */
class SystemManager
{
    public:
        /**
         * @brief Create and Initialize the SystemManager.
         */
        SystemManager();

        /**
         * @brief Will update all managers that were registered with the given updateStep.
         *
         * @param delta The amount of time in ms that has passed since the last update
         * @param updateStep Determines which managers should be updated
         */
        void Update(float delta, UpdateStepEnum updateStep);

        /**
         * @brief Delete the entity and free any components used by it.  An entity can only
         * be deleted once.  After an entity is deleted no reference to it or any of its
         * components should be used again.
         *
         * @param entity Entity that should be deleted.
         */
        void DeleteEntity(Entity entity);

        /**
         * @brief Create a new unique Entity.
         *
         * @return A new entity
         */
        Entity CreateEntity();

        /**
         * @brief Register the System with the system manager.  This is needed in order for the
         * SystemManager to notify a system if an entity is deleted.  A system can only be
         * registered once.
         *
         * This method should only be called by the system that is being registered.
         *
         * @param system System that is being registered
         * @param updateStep Step that determines when the system is updated
         */
        void RegisterSystem(AbstractSystem * system, UpdateStepEnum updateStep);

        /**
         * @brief Called when a system is creating a new component for an entity.  This
         * method must be called in order for the system to be notified when the entity is
         * deleted.
         *
         * This method should only be called by the system that is being registered.
         *
         * @param entity Entity that the component is added to
         * @param owningSystem System that will control the component
         */
        void RegisterComponent(Entity entity, AbstractSystem * owningSystem);

        /**
         * @brief Called when a system is removing a component from an entity.
         *
         * This method should only be called by the system that contains the entity.
         *
         * @param entity Entity whose component is being deleted.
         * @param owningSystem System that is deleting the component.
         */
        void UnregisterComponent(Entity entity, AbstractSystem * owningSystem);

    private:
        /**
         * @brief Used to track which systems are controlled by the manager and
         * when they should be updated.
         */
        std::map< UpdateStepEnum, std::vector<AbstractSystem * > > _systems;
        /**
         * @brief Used to track which systems manage a component for each entity
         */
        std::unordered_map< Entity, std::set<AbstractSystem * > > _components;
        /**
         * @brief Highest id that has been assigned to an entity.  Used to assign 
         * unique ids 
         */
        unsigned int _maxEntityId;
};

}
#endif 
