#ifndef Ancona_Core2D_Systems_PathFollowerSystem_H_
#define Ancona_Core2D_Systems_PathFollowerSystem_H_

#include <Ancona/Core2D/Systems/PathSystem.hpp>
#include <Ancona/Core2D/Systems/Position/PositionSystem.hpp>
#include <Ancona/Framework/EntityFramework/UnorderedSystem.hpp>
#include <Ancona/Framework/Serializing/Serializing.hpp>

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
        PositionComponent * _positionComponent;
        
        /* serialized properties */
        Entity _pathEntity = nullentity;

        /* other properties */
        sf::Vector2f _pointToMoveTowards;
        
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
