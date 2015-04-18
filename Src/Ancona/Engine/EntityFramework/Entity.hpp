#ifndef Ancona_Engine_EntityFramework_Entity_H_
#define Ancona_Engine_EntityFramework_Entity_H_

namespace ild
{
/**
 * @brief Entity is used as a key to identify components in the Entity Systems.  You can assume that the entities are well ordered.
 * I.E. you can use >, <, <=, >=, ==, and != on the entities.
 * @author Jeff Swenson
 */
typedef unsigned int Entity ;

const Entity nullentity = ~0u;

}

#endif
