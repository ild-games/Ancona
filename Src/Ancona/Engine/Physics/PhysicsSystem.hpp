#ifndef Ancona_Engine_Physics_PhysicsSystem_hpp
#define Ancona_Engine_Physics_PhysicsSystem_hpp

#include <memory>

#include <Ancona/Engine/Physics/Position.hpp>
#include <Ancona/Engine/Physics/Actions.hpp>

namespace ild
{

class PhysicsComponent
{
    public:
        void Update(float delta);

        inline Actions & GetActions() { return _actions; }
        inline Position & GetPosition() { return _position; }
    private:
        Position _position;
        Actions _actions;
};

class PhysicsSystem
{
    public:
        PhysicsSystem(SystemManager & manager);
        
        void Update(float delta);

        PhysicsComponent * CreateComponent(const Entity & entity);
    private:
};

}
#endif
