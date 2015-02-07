#include <Ancona/Engine/Physics/PlatformPhysicsSystem.hpp>

using namespace ild;

PlatformPhysicsComponent::PlatformPhysicsComponent(Point location)
{
    _position.SetPosition(location);
}

void PlatformPhysicsComponent::Update(float delta)
{
    _actions.Apply(_position, delta);
}

PlatformPhysicsSystem::PlatformPhysicsSystem(SystemManager & manager)
    : BasePhysicsSystem(manager)
{
    
}

void PlatformPhysicsSystem::Update(float delta)
{
    for(EntityComponentPair pair : *this)
    {
        static_cast<PlatformPhysicsComponent *>(pair.second)->Update(delta);
    }
}

PlatformPhysicsComponent * PlatformPhysicsSystem::operator[] (const Entity & entity) 
{
    return static_cast<PlatformPhysicsComponent *>(BasePhysicsSystem::at(entity));
}

PlatformPhysicsComponent * PlatformPhysicsSystem::at (const Entity & entity) 
{
    return (*this)[entity];
}

PlatformPhysicsComponent * PlatformPhysicsSystem::CreateComponent(const Entity & entity, Point location)
{
    PlatformPhysicsComponent * component = new PlatformPhysicsComponent(location);
    
     AttachComponent(entity, component);
}


