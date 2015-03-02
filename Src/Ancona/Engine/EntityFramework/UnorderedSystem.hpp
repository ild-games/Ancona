#ifndef Ancona_Engine_EntityFramework_UnorderedSystem_H_
#define Ancona_Engine_EntityFramework_UnorderedSystem_H_

#include <unordered_map>

#include <Ancona/Engine/EntityFramework/AbstractSystem.hpp>
#include <Ancona/Engine/EntityFramework/Entity.hpp>
#include <Ancona/Engine/EntityFramework/SystemManager.hpp>
#include <Ancona/Engine/EntityFramework/UpdateStep.hpp>
#include <Ancona/Engine/Loading/Loading.hpp>
#include <Ancona/Util/Assert.hpp>

namespace ild
{

class SystemManager;

/**
 * @brief Implements most of the logic needed by a system for tracking components.
 * Any system that does not need its components stored in a specific order should 
 * inherit from this class.
 *
 * @owner Jeff Swenson
 *
 * @tparam ComponentType The type of component that the system manages.
 */
template <class ComponentType>
class UnorderedSystem : public AbstractSystem
{
    public:
        /**
         * @brief Construct and initialize the UnorderedSystem.  The system will
         * register itself with the SystemManager.
         *
         * @param manager The SystemManager that owns BaseSystem
         * @param updateStep Determine when the system is updated
         */
        UnorderedSystem(SystemManager & manager, UpdateStepEnum updateStep) :
            AbstractSystem("", manager, updateStep)
        {  }

        /**
         * @brief Construct and initialize the UnorderedSystem with a name.  The system will
         * register itself with the SystemManager.
         *
         * @param systemName Name of the system.
         * @param manager The SystemManager that owns BaseSystem
         * @param updateStep Determine when the system is updated
         */
        UnorderedSystem(
                std::string systemName,
                SystemManager & manager, 
                UpdateStepEnum updateStep) :
            AbstractSystem(systemName, manager, updateStep)
        { }

        /**
         * @brief Get the component corresponding to the entity.
         * If the entity does not have a component managed by the system then null
         * will be returned.
         *
         * @param entity Entity whose component is being requested.
         *
         * @return A reference to the component if it exists
         */
        ComponentType * operator [] (const Entity & entity)
        {
            auto componentIter = _components.find(entity);
            if(componentIter != _components.end())
            {
                return componentIter->second;
            }
            return NULL;
        }

        ComponentType * at(const Entity & entity)
        {
            return (*this)[entity];
        }

        /**
         * @brief Implementation for AbstractSystem method
         */
        void Update(float delta) = 0;

        /**
         * @brief Implementation for AbstractSystem method
         */
        void RemoveComponent(const Entity & entity)
        {
            Assert(_components.find(entity) != _components.end(),
                    "Can not remove a component that does not exist");

            EntityIsDeleted(entity); 
            _systemManager.UnregisterComponent(entity, this);
        }

        /**
         * @brief Implementation for AbstractSystem method
         *
         * NOTE: This method should only be called by SystemManager
         */
        void EntityIsDeleted(const Entity & entity)
        {
            Assert(_components.find(entity) != _components.end(),
                    "A system should not be notified of an entities deletion if the \
                    system does not contain a component for the entity");

            auto componentIter = _components.find(entity);
            ComponentType * component = componentIter->second;

            //Allow a child class to react to the component being removed
            OnComponentRemove(entity, component);

            _components.erase(componentIter);
            //Since the component is now unreachable it should be deleted.
            delete component; 
        }

        /**
         * @brief Default implementation of GetInflater.  By default it returns a null inflater.
         *
         * @return A unique_ptr to an inflater created by a child class.  If the child class did not implement
         * the method then it will be null.
         */
        std::unique_ptr<AbstractInflater> GetInflater() override
        {
            return std::unique_ptr<AbstractInflater>(new DynamicInflater<UnorderedSystem<ComponentType>>(*this));
        }

        /**
         * @brief Inflates the unordered system.
         */
        void * Inflate(
                const Json::Value & object,
                const Entity entity,
                LoadingContext * loadingContext) override
        {
            Assert(false, "No inflater defined for this system");
            return NULL;
        }



    protected:
        /**
         * @brief EntityComponentIter is an iterator that can be used to iterate over all contained
         * components.
         */
        typedef typename std::unordered_map<Entity, ComponentType *>::iterator EntityComponentIter;
        
        /**
         * @brief EntityComponentPair should be used as the types in for each loops iterating over the component
         */
        typedef typename std::pair<const Entity, ComponentType *> & EntityComponentPair;

        /**
         * @brief This method can be overriden to allow a child class to respond when
         * a component is being removed. It will be called just before the system
         * removes it and deregisters it.
         *
         * @param entity Entity that component is being removed from
         * @param component Component that is being removed
         */
        virtual void OnComponentRemove(Entity entity, ComponentType * component) {};

        /**
         * @brief Get at iterator to the first component in the system.  No order of 
         * components is guaranteed
         *
         * @return An iterator that can be used to iterate over the components
         */
        EntityComponentIter begin()
        {
            return _components.begin();
        }

        /**
         * @brief Get the end iterator for the system.
         *
         * @return The end iterator.
         */
        EntityComponentIter end()
        {
            return _components.end();
        }

        /**
         * @brief Used by child classes to add components to an entity.  Attach component will
         * register the component with SystemManager.
         *
         * @param entity Component that should be attached to the entity
         * @param component Entity to attach the component to
         */
        void AttachComponent(const Entity & entity, ComponentType * component)
        {
            Assert(component != NULL, "Can not attach a null component");
            Assert(_components.find(entity) == _components.end(),
                    "Can not attach two of the same component to an entity");

            _components[entity] = component;
            _systemManager.RegisterComponent(entity, this);
        }

    private:
        /**
         * @brief Used to store components
         */
        std::unordered_map<Entity, ComponentType *> _components;
};

}
#endif
