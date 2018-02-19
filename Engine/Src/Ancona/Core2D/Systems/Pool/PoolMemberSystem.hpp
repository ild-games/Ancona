#ifndef Ancona_Core2D_Systems_Pool_PoolMemberSystem_H_
#define Ancona_Core2D_Systems_Pool_PoolMemberSystem_H_

#include <Ancona/Framework/EntityFramework/UnorderedSystem.hpp>
#include <Ancona/Framework/Serializing/Serializing.hpp>

namespace ild
{

////////// TEMPLATIZED SYSTEM SETUP INSTRUCTIONS
/// Before using this you must initialize an instance of the template in your GameSystems class

/**
 * @brief { PoolMemberComponent description }
 */
class PoolMemberComponent
{
    public:
        /**
         * Construct a blank PoolMemberComponent for serialization.
         */
        PoolMemberComponent();

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
};

/**
 * @brief { PoolMemberSystem description }
 */
class PoolMemberSystem : public UnorderedSystem<PoolMemberComponent>
{
    public:
        PoolMemberSystem(
                std::string name,
                SystemManager & manager);

        void Update(float delta) override;

        PoolMemberComponent * CreateComponent(
                const Entity & entity);

};

}

#endif
