#ifndef Ancona_Core2D_Systems_TriggerDeathSystem_H_
#define Ancona_Core2D_Systems_TriggerDeathSystem_H_

#include <Ancona/Core2D/Systems/Drawable/AnimatedDrawable.hpp>
#include <Ancona/Core2D/Systems/Drawable/DrawableSystem.hpp>
#include <Ancona/Framework/EntityFramework/UnorderedSystem.hpp>
#include <Ancona/Framework/Serializing/Serializing.hpp>

namespace ild
{

/**
 * @brief Component used to trigger a death for an entity.
 */
class TriggerDeathComponent
{
  public:
    /**
     * Construct a blank TriggerDeathComponent for serialization.
     */
    TriggerDeathComponent();

    /**
     * @copydoc ild::CameraComponent::FetchDependencies
     */
    void FetchDependencies(const Entity &entity);

    /**
     * @copydoc ild::CameraComponent::Serialize
     */
    void Serialize(Archive &arc);

    /**
     * @brief Update step where the component logic happens.
     */
    void Update(float delta);

  private:
    SystemManager *_systemManager;
    DrawableSystem *_drawableSystem;
    AnimatedDrawable *_animation;
    std::string _animationToWatch;
    Entity _entity = nullentity;
};

class TriggerDeathSystem : public UnorderedSystem<TriggerDeathComponent>
{
  public:
    TriggerDeathSystem(std::string name, SystemManager &manager);

    void Update(float delta) override;

    TriggerDeathComponent *CreateComponent(const Entity &entity);
};

} // namespace ild

#endif
