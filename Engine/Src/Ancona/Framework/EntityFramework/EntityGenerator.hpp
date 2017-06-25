#ifndef Ancona_Framework_EntityFramework_EntityGenerator
#define Ancona_Framework_EntityFramework_EntityGenerator

#include <atomic>

#include <Ancona/Util/Assert.hpp>
#include "./Entity.hpp"

namespace ild
{

class EntityGenerator
{
    public:
        Entity NextEntity()
        {
            auto next = _maxEntityId++;
            Assert(_maxEntityId != ~0u, "Entity key has overflown");
            return next++;
         }

    private:
        std::atomic<Entity> _maxEntityId{0u};
};

} /* ild */

#endif /* end of include guard: Ancona_Framework_EntityFramework_EntityGenerator */
