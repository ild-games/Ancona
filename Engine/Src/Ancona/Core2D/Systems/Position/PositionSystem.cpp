#include <Ancona/Core2D/Systems/Position/PositionSystem.hpp>

REGISTER_POLYMORPHIC_SERIALIZER(ild::PositionComponent);

namespace ild {
std::ostream & operator << (std::ostream& os, const Point&pt)
{
    os << "(" << pt.x << "," << pt.y << ")";
    return os;
}

std::ostream & operator << (std::ostream&& os, const Point&pt)
{
    os << "(" << pt.x << "," << pt.y << ")";
    return os;
}
}

using namespace ild;


PositionSystem::PositionSystem(
        std::string systemName,
        SystemManager & manager) :
    UnorderedSystem<PositionComponent>(
            systemName,
            manager,
            UpdateStep::Physics)
{

}

void PositionSystem::Update(float delta) {
    for(EntityComponentPair pair : *this)
    {
        pair.second->Update(delta);
    }
}

PositionComponent * PositionSystem::CreateComponent(const Entity & entity) {
    auto comp = new PositionComponent();
    AttachComponent(entity, comp);
    return comp;
}

bool PositionComponent::onGround() const
{
    return _groundDirection != Point();
}

void PositionComponent::Serialize(Archive & arc)
{
    arc(_position, "position");
    arc(_velocity, "velocity");
}

void PositionComponent::Update(float delta) {
    if (_velocity.x != 0.0f || _velocity.y != 0.0f) 
    {
        _position += delta * _velocity;
        _position.x = roundf(_position.x * 100) / 100;
        _position.y = roundf(_position.y * 100) / 100;
    }
}
