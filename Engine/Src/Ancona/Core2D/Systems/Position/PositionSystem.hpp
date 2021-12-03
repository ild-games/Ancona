#ifndef Ancona_Engine_Position_PositionSystem_hpp
#define Ancona_Engine_Position_PositionSystem_hpp

#include <Ancona/Framework/EntityFramework/UnorderedSystem.hpp>
#include <Ancona/Framework/Serializing/Serializing.hpp>
#include <Ancona/Util/Vector2.hpp>

namespace ild
{

/**
 * @brief Operator used to output a Vector2f to an out stream. The Vector2f will be formatted as (x,y)
 */
std::ostream &operator<<(std::ostream &os, const Vector2f &pt);

class PositionComponent
{
  public:
    /**
     * @brief Overriable default destructor.
     */
    ~PositionComponent()
    {
    }

    /**
     * @copydoc ild::CameraComponent::Serialize
     */
    void Serialize(Archive &arc);

    /**
     * @copydoc ild::CameraComponent::FetchDependencies
     */
    void FetchDependencies(const Entity &entity);

    void Update(float delta);

    /* getters and setters */
    inline const Vector2f &position() const
    {
        return _position;
    }
    inline const Vector2f &velocity() const
    {
        return _velocity;
    }
    inline void velocity(const Vector2f &velocity)
    {
        _velocity = velocity;
    }
    void position(const Vector2f &position);

  protected:
    Vector2f _actualPosition;
    Vector2f _position;
    Vector2f _velocity;

    void RoundPosition();
};

/**
 * @brief A Base Position System that allows access
 *  to information that is not closely tied to a games world.
 * @author Jeff Swenson
 */
class PositionSystem : public UnorderedSystem<PositionComponent>
{
  public:
    /**
     * @brief Constructor of a PositionSystem and register it with the manager.
     *
     * @param systemName Name of the system.
     * @param manager Manager that the system belongs to.
     */
    PositionSystem(std::string systemName, SystemManager &manager);

    /**
     * Create a position component at (0,0)
     * @param Entity entity to create the component for.
     */
    PositionComponent *CreateComponent(const Entity &entity);

  protected:
    /**
     * @brief Update the position components.  Must be implemented by the child position system.
     *
     * @param delta Fraction of a second since the last update.
     */
    void Update(float delta);
};

} // namespace ild
#endif
