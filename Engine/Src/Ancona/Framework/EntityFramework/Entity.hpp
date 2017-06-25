#ifndef Ancona_Engine_EntityFramework_Entity_H_
#define Ancona_Engine_EntityFramework_Entity_H_

#include <string>

namespace ild
{
/**
 * @brief Entity is used as a key to identify components in the Entity Systems.  You can assume that the entities are well ordered.
 * I.E. you can use >, <, <=, >=, ==, and != on the entities.
 */
typedef unsigned int Entity ;

/**
 * Entities are stored in map files with a string key. If an entity system contains multiple maps
 * the key is not unique. This class combines the entity key with the map key. This allows most instances of
 * code to refer to the entity with a single class.
 * @param entityKey Key that identifies an entity within a map.
 * @param mapKey    Key that identifies the map the entity belongs to.
 */
class EntityKey {
    public:
        EntityKey(const std::string & entityKey, const std::string & mapKey)
            : _entityKey(entityKey), _mapKey(mapKey) {}

        const std::string entityKey() const { return _entityKey; }
        const std::string mapKey() const { return _mapKey; }

        bool operator == (const EntityKey & other) const {
            return other._entityKey == _entityKey && other._mapKey == _mapKey;
        }
private:
    std::string _entityKey;
    std::string _mapKey;
};

/**
 * Constant that represents the lack of an entity.
 */
const Entity nullentity = ~0u;

}

namespace std
{
    template<> struct hash<ild::EntityKey>
    {
        std::size_t operator()(ild::EntityKey const& key) const
        {
            auto h1 = std::hash<std::string>{}(key.entityKey());
            auto h2 = std::hash<std::string>{}(key.mapKey());
            return h1 ^ (h2 << 1);
        }
    };
}

#endif
