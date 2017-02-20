#ifndef Ancona_Core2D_Systems_PathFollowerSystem_H_
#define Ancona_Core2D_Systems_PathFollowerSystem_H_

#include <Ancona/Core2D/Systems/PathSystem.hpp>
#include <Ancona/Core2D/Systems/Position/PositionSystem.hpp>
#include <Ancona/Framework/EntityFramework/UnorderedSystem.hpp>
#include <Ancona/Framework/Serializing/Serializing.hpp>
#include <Ancona/Platformer/Actions/ActionSystem.hpp>

namespace ild
{

/**
 * @brief Used to follow an associated PathComponent
 */
class PathFollowerComponent
{
    public:
        /**
         * Construct a blank PathFollowerComponent for serialization.
         */
        PathFollowerComponent();

        /**
         * @copydoc ild::CameraComponent::FetchDependencies
         */
        void FetchDependencies(const Entity & entity);

        /**
         * @copydoc ild::CameraComponent::Serialize
         */
        void Serialize(Archive & arc);

        /**
         * @brief Update step where the component logic happens.
         */
        void Update(float delta);

    private:
        /* cached off systems and components */
        PathSystem * _pathSystem;
        PathComponent * _pathComponent;
        PositionSystem * _positionSystem;
        PositionComponent * _pathPositionComponent;
        ActionSystem * _actionSystem;
        ActionComponent * _actionComponent;
        
        /* serialized properties */
        Entity _pathEntity = nullentity;

        /* other properties */
        int _nextVertexIndex = 0;
        VectorActionProxy _action;
        Entity _entity = nullentity;
        int _followDirection = 1;

        void StartNextPathSegment();
        bool IsNextVertexValid();
};

class PathFollowerSystem : public UnorderedSystem<PathFollowerComponent>
{
    public:
        PathFollowerSystem(
                std::string name,
                SystemManager & manager);

        void Update(float delta) override;

        PathFollowerComponent * CreateComponent(
                const Entity & entity);

};

}

#endif
