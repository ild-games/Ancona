#ifndef Ancona_Platformer_Action_ActionSystem_hpp
#define Ancona_Platformer_Action_ActionSystem_hpp

#include <memory>
#include <string>

#include <Ancona/Core2D/Systems/Position/PositionSystem.hpp>
#include <Ancona/Framework/Serializing/SerializingContext.hpp>

#include "Actions.hpp"

namespace ild
{

class ActionSystem;

/**
 * @brief Component for the ActionSystem
 * @author Jeff Swenson
 */
class ActionComponent
{
    public:
        /**
         * @brief Initialize a new action copmonent
         *
         * @param actionSystem Action system that the component belongs to.
         */
        ActionComponent(ActionSystem * actionSystem);


        /**
         * @brief Default constructor that should only be used for serialization.
         */
        ActionComponent() { }

        /**
         * @brief Update the component.  This will apply any active actions to the entities state.
         */
        void Update(float delta);

        /**
         * @copydoc ild::CameraComponent::Serialize
         */
        void Serialize(Archive & arc);

        /**
         * @copydoc ild::CameraComponent::FetchDependencies
         */
        void FetchDependencies(const Entity & entity);

        /* getters and setters */
        inline Actions & actions() { return _actions; }
    private:
        Actions _actions;
        PositionSystem * _positionSystem;
        PositionComponent * _position;
};

/**
 * @brief Platform position system provides behavior that is designed for a platformer game.
 * @author Jeff Swenson
 */
class ActionSystem : public UnorderedSystem<ActionComponent>
{
    public:

        /**
         * @brief Construct and initialize the ActionSystem.
         *
         * @param systemName Name of the system.
         * @param manager System manager the position system belongs to.
         * @param positionSystem System that tracks the position of the entities.
         */
        ActionSystem(
                std::string systemName,
                SystemManager & manager,
                PositionSystem * positionSystem);

        /**
         * @brief Update all of the components in the action system
         *
         * @param delta Time passed in seconds since the last update.
         */
        void Update(float delta);

        /**
         * @brief Create a Action Component and add it to the system.
         *
         * @param entity Entity to add the component to.
         *
         * @return A pointer to the position component.
         */
        ActionComponent * CreateComponent(const Entity & entity);

        /** Getters and Setters */
        PositionSystem * positionSystem() { return _positionSystem; }
    private:
        /**
         * @brief A vector describing the direction and magnitude of gravity.
         */
        Point _gravity;
        PositionSystem * _positionSystem;
};

}
#endif
