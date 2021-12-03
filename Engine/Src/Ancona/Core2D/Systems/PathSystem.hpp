#ifndef Ancona_Core2D_Systems_PathSystem_H_
#define Ancona_Core2D_Systems_PathSystem_H_

#include <Ancona/Framework/EntityFramework/UnorderedSystem.hpp>
#include <Ancona/Framework/Serializing/Serializing.hpp>
#include <Ancona/Util/Vector2.hpp>

namespace ild
{

/**
 * @brief Describes a path for other entities to follow
 */
class PathComponent
{
  public:
    /**
     * Construct a blank PathComponent for serialization.
     */
    PathComponent();

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

    float TimeForSegment(int segment);

    /* getters and setters */
    std::vector<Vector2f> &vertices()
    {
        return _vertices;
    }
    bool isLoop()
    {
        return _isLoop;
    }

  private:
    std::vector<Vector2f> _vertices;
    bool _isLoop;
    float _cycleTime;

    float DistanceForSegment(int segment);
    float TotalDistance();
};

class PathSystem : public UnorderedSystem<PathComponent>
{
  public:
    PathSystem(std::string name, SystemManager &manager);

    void Update(float delta) override;

    PathComponent *CreateComponent(const Entity &entity);
};

} // namespace ild

#endif
