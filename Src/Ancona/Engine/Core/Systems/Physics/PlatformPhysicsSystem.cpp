#include <Ancona/Engine/Core/Systems/Physics/PlatformPhysicsSystem.hpp>

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

void * PlatformPhysicsSystem::Inflate(
        const Json::Value & object,
        const Entity entity,
        LoadingContext * loadingContext)
{
    PlatformPhysicsComponent * position = loadingContext->GetSystems().GetSystem<PlatformPhysicsSystem>("physics")->CreateComponent(entity);
    for(Json::Value actionsJson : object["actions"]["list"])
    {
        if(actionsJson["type"].asString() == "position")
        {
            position->GetActions().CreatePositionAction()
                ->Value(Point(actionsJson["value"]["x"].asFloat(), actionsJson["value"]["y"].asFloat()))
                ->Tween(actionsJson["tween"].asFloat())
                ->Duration(actionsJson["duration"].asFloat());
        }
        else if(actionsJson["type"].asString() == "velocity")
        {
            position->GetActions().CreateVelocityAction()
                ->Value(Point(actionsJson["value"]["x"].asFloat(), actionsJson["value"]["y"].asFloat()))
                ->Tween(actionsJson["tween"].asFloat())
                ->Duration(actionsJson["duration"].asFloat());
        }
    }
    if(object["actions"]["gravity"].asBool()) 
    {
        position->GetActions().SetAffectedByGravity(true);
    }
    return nullptr;
}
