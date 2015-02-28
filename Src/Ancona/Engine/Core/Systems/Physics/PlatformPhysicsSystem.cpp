#include <Ancona/Engine/Core/Systems/Physics/PlatformPhysicsSystem.hpp>

#include <iostream> //TODO Remove

using namespace ild;

PlatformPhysicsComponent::PlatformPhysicsComponent(Point location, BasePhysicsSystem & physicsSystem) 
    : _actions(physicsSystem)
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
    PlatformPhysicsComponent * component = new PlatformPhysicsComponent(location, *this);
    
    AttachComponent(entity, component);

    return component;
}

void * PlatformPhysicsSystem::Inflate(const Json::Value & object)
{
    std::cout << "PPS::Inflate" << std::endl;
    return nullptr;
}
