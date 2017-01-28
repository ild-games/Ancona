#ifndef Ancona_Engine_Core_Systems_Collision_Collision_H_
#define Ancona_Engine_Core_Systems_Collision_Collision_H_

#include <Ancona/Framework/EntityFramework/Entity.hpp>

namespace ild {

class CollisionComponent;

class Collision {
    public:
        Collision(Entity entity, CollisionComponent * component) : _entity(entity), _component(component) {}

        Entity entity() { return _entity; }
        CollisionComponent * collisionComponent() { return _component; }

    private:
        Entity _entity;
        CollisionComponent * _component;
};

}

#endif
