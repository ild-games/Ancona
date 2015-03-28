#include <Ancona/Engine/Core/Systems/Physics/PlatformPhysicsSystem.hpp>

//TODO remove iostream
#include <iostream>

using namespace ild;

PlatformPhysicsComponent::PlatformPhysicsComponent(Point location, BasePhysicsSystem & physicsSystem) 
    : _actions(&physicsSystem)
{
    _position.SetPosition(location);
}

void PlatformPhysicsComponent::Serialize(Archive & archive)
{
    //TODO archive(_actions, "Actions"); 
    archive.system(_system,"physics");

    if (archive.IsLoading()) {
    }

    archive(_actions, "Actions");
}

void PlatformPhysicsComponent::Update(float delta)
{
    _actions.Apply(_position, delta);
}

void PlatformPhysicsComponent::FetchDependencies()
{
    _actions.SetPhysics(_system);
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
    PlatformPhysicsComponent * component = new PlatformPhysicsComponent(location, *this);
    
    AttachComponent(entity, component);

    return component;
}

namespace ild {
template <>
struct Serializer<decltype(PlatformPhysicsSystem::_components)>
{
    static void Serialize(std::unordered_map<Entity, BasePhysicsComponent *> & property, Archive & arc) 
    {
        if (arc.IsLoading())
        {
            PlatformPhysicsSystem * system;

            arc.system(system,"physics");

            for(auto entityKey : arc.GetTopJson()->getMemberNames())
            {
                PlatformPhysicsComponent * value = new PlatformPhysicsComponent();
                arc(*value, entityKey);
                auto entity = arc.GetEntity(entityKey);
                property[entity] = value;
            }
        }
    }
};
}

void PlatformPhysicsSystem::Serialize(Archive & arc)
{
    arc(_components, "Components");

    if(arc.IsLoading())
    {
        for(EntityComponentPair comp : _components) 
        {
            AttachComponent(comp.first, comp.second);
        }
    } 
}
