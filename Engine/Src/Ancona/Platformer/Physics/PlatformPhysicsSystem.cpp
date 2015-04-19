#include <Ancona/Platformer/Physics/PlatformPhysicsSystem.hpp>

REGISTER_POLYMORPHIC_SERIALIZER(ild::PlatformPhysicsComponent);

using namespace ild;

PlatformPhysicsComponent::PlatformPhysicsComponent(
        Point location, 
        PlatformPhysicsSystem * physicsSystem) :
    _actions(physicsSystem),
    _system(physicsSystem)
{
    _position.position(location);
}

void PlatformPhysicsComponent::Serialize(Archive & archive)
{
    archive.system(_system,"physics");
    archive(_actions, "actions");
}

void PlatformPhysicsComponent::Update(float delta)
{
    _actions.Apply(_position, delta);
}

void PlatformPhysicsComponent::FetchDependencies(const Entity & entity)
{
    _actions.physics(_system);
}

PlatformPhysicsSystem::PlatformPhysicsSystem(
        std::string systemName,
        SystemManager & manager) : 
    BasePhysicsSystem(systemName, manager)
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
    PlatformPhysicsComponent * component = new PlatformPhysicsComponent(location, this);
    
    AttachComponent(entity, component);

    return component;
}
