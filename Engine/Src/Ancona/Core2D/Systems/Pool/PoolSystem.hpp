#ifndef Ancona_Core2D_Systems_Pool_PoolSystem_H_
#define Ancona_Core2D_Systems_Pool_PoolSystem_H_

#include <Ancona/Framework/EntityFramework/UnorderedSystem.hpp>
#include <Ancona/Framework/Serializing/Serializing.hpp>
#include <Ancona/Util2D/Collision/Box2.hpp>

namespace ild
{

////////// TEMPLATIZED SYSTEM SETUP INSTRUCTIONS
/// Before using this you must initialize an instance of the template in your GameSystems class

/**
 * @brief { PoolComponent description }
 */
class PoolComponent
{
    public:
        /**
         * Construct a blank PoolComponent for serialization.
         */
        PoolComponent();

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
        std::vector<Entity> _pool;

        std::function<void(Entity)> _reset;
};

/**
 * @brief { PoolSystem description }
 */
class PoolSystem : public UnorderedSystem<PoolComponent>
{
    public:
        PoolSystem(
                std::string name,
                SystemManager & manager);

        void Update(float delta) override;

        PoolComponent * CreateComponent(
                const Entity & entity);

        Entity GetEntity();
        Entity ReturnEntity(const Entity & entity);

};

}

#endif
