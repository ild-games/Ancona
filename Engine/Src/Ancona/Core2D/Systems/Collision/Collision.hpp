#ifndef Ancona_Engine_Core_Systems_Collision_Collision_H_
#define Ancona_Engine_Core_Systems_Collision_Collision_H_

#include <SFML/System.hpp>
#include <Ancona/Framework/EntityFramework/Entity.hpp>

namespace ild {

class CollisionComponent;

class Collision {
    public:
        Collision(Entity entity, CollisionComponent * component, sf::Vector2f fixNormal, float magnitude)
            : _fixNormal(fixNormal), _entity(entity), _component(component),  _fixMagnitude(magnitude) {}

        Entity entity() { return _entity; }
        CollisionComponent * collisionComponent() { return _component; }
        sf::Vector2f fixNormal() { return _fixNormal; }
        float fixMagnitude() { return _fixMagnitude; }

        bool operator == (const ild::Collision & right) {
            return right._entity == _entity &&
                right._fixNormal == _fixNormal &&
                right._fixMagnitude == _fixMagnitude;
        }

    private:
        sf::Vector2f _fixNormal;
        Entity _entity;
        CollisionComponent * _component;
        float _fixMagnitude;
};

}

#endif
