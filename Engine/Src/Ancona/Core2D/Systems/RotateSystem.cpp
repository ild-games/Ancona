#include <Ancona/Core2D/Systems/RotateSystem.hpp>

using namespace ild;

/* Component */
RotateComponent::RotateComponent(RotateSystem *rotateSystem) : _drawableSystem(rotateSystem->drawableSystem())
{
}

void RotateComponent::Update(float delta)
{
    float rotation = _drawableComponent->topDrawable()->rotation();
    rotation += _speed * delta;
    _drawableComponent->topDrawable()->rotation(rotation);
    for (auto &drawableKey : _drawablesSpeeds)
    {
        Drawable *drawable = _drawableComponent->GetDrawable(drawableKey.first);
        rotation = drawable->rotation();
        rotation += drawableKey.second * delta;
        drawable->rotation(rotation);
    }
}

void RotateComponent::Serialize(Archive &arc)
{
    arc(_speed, "speed");
    arc(_drawablesSpeeds, "drawablesSpeeds");
    arc.system(_drawableSystem, "drawable");
}

void RotateComponent::FetchDependencies(const Entity &entity)
{
    _drawableComponent = _drawableSystem->at(entity);
}

/* System */
RotateSystem::RotateSystem(std::string name, SystemManager &manager, DrawableSystem *drawableSystem)
    : UnorderedSystem(name, manager, UpdateStep::Update), _drawableSystem(drawableSystem)
{
}

void RotateSystem::Update(float delta)
{
    for (EntityComponentPair comp : *this)
    {
        comp.second->Update(delta);
    }
}

RotateComponent *RotateSystem::CreateComponent(const Entity &entity)
{
    RotateComponent *comp = new RotateComponent(this);
    AttachComponent(entity, comp);
    return comp;
}
