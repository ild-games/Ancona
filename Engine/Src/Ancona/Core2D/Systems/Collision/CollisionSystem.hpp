#pragma once

#include <Ancona/Core2D/Systems/Collision/CollisionComponent.hpp>
#include <Ancona/Core2D/Systems/PositionSystem.hpp>
#include <Ancona/Framework/EntityFramework/UnorderedSystem.hpp>
#include <Ancona/Util/Data.hpp>
#include <Ancona/Util/Vector2.hpp>
#include <Ancona/Util/Vector3.hpp>
#include <functional>
#include <vector>

namespace ild
{

/**
 * @brief Function signature used by the collision system.
 */
typedef std::function<void(const Entity &, const Entity &, const Vector2f &, float)> CollisionCallback;

/**
 * @brief System used to provide collision interactions and callbacks for entities.
 * @author Jeff Swenson
 */
class CollisionSystem : public UnorderedSystem<CollisionComponent>
{
  public:
    /**
     * @brief Construct a collision system and register it with the manager.
     *
     * @param name The systems name used for loading.
     * @param manager Manager that the system belongs to.
     * @param positions System that defines the position of an entity.
     */
    CollisionSystem(const std::string &name, SystemManager &manager, PositionSystem &positions);

    void OnLoad() override;

    /**
     * @brief Update the position for all components based off of their velocity
     *
     * @param delta Number of ms since last update
     */
    void Update(float delta) override;

    /**
     * @brief Create and attach a collision component for the entity.
     *
     * @param entity Entity that the component is attached to.
     * @param dim Dimension for the entity to be used for collision.
     * @param type The collision type of the entity.
     * @param bodyType The body type of the entity.  Determines how collision fixing
     *  is handled for it. Defaults to BodyType::None.
     *
     * @return A pointer to the component.
     */
    CollisionComponent *CreateComponent(
        const Entity &entity,
        const Vector3f &dim,
        CollisionType type,
        BodyTypeEnum bodyType = BodyType::None);

    /**
     * Find the entities that collide with the box.
     *
     * @param box Collision box used to find entities.
     *
     * @return An array of entity collision component pairs.
     */
    void GetEntitiesInBox(std::vector<Collision> &collisions, const Box2 &box, const CollisionComponent *ignore);

    /**
     * @brief Create a Type that can be assigned to a component.
     *
     * @param key describing the collision type.
     *
     * @return A unique Collision Type.
     */
    CollisionType CreateType(const std::string &key);

    /**
     * @brief Get the collision type associated with the key.
     */
    const CollisionType &GetType(const std::string &key) const;

    /**
     * @brief Get the key associated with the collision type.
     *
     * @type CollisionType used to get the key from.
     */
    const std::string &GetKeyFromType(const CollisionType &type);

    /**
     * @brief Define the handler that will be used for the collisions between the two types.
     *
     * @param typeA One type involved in the collision.
     * @param typeB The second type involved in the collision.
     * @param callback The callback will be called as callback(entityA, entityB) where
     *  entityA is an entity of the first type and entityB is an entity of second type.
     */
    void DefineCollisionCallback(CollisionType typeA, CollisionType typeB, CollisionCallback callback);

    /**
     * @brief Determine if the collision type has already been created.
     *
     * @param key Key that was used to create the collision type.
     *
     * @return True if the collision type is defined.  False otherwise.
     */
    bool IsCollisionTypeDefined(const std::string &key) const;

    /**
     * Check if the body type can be the source of collisions. Example: We don't
     * check the collision of environment body types. We only check if solid bodys
     * are colliding with the environment.
     * @param  type Type of collision we are testing.
     * @return      True if the type will be checked for collision.
     */
    bool DoesTypeDetectCollisions(BodyTypeEnum type);

    /* Getters and Setters */
    PositionSystem &position() { return _positions; }
    void maxSlope(float value) { _maxSlope = value; }
    CollisionType noneType() const;

  private:
    int _nextType;
    Table<CollisionCallback> _callbackTable;
    PositionSystem &_positions;
    std::unordered_map<std::string, CollisionType> _collisionTypes;
    std::unordered_map<CollisionType, std::string> _collisionTypeToKey;
    float _maxSlope = 45;
    const std::string NONE_COLLISION_TYPE = "none";
    const std::string COLLISION_TYPE_MUST_EXIST_MSG = "The collision type must exist";

    bool UniqueCollision(EntityComponentPair &entityA, EntityComponentPair &entityB);
    void HandleCollision(
        EntityComponentPair &pairA,
        EntityComponentPair &pairB,
        const Vector2f &fixNormal,
        float fixMagnitude);
    bool EntitiesOverlapping(float fixMagnitude);

    void FixCollision(CollisionComponent *a, CollisionComponent *b, const Vector2f &fixNormal, float fixMagnitude);

    void PushApart(CollisionComponent *a, CollisionComponent *b, const Vector2f &correctFix);
    void PushFirstOutOfSecond(CollisionComponent *a, CollisionComponent *b, const Vector2f &correctFix);
};

} // namespace ild
