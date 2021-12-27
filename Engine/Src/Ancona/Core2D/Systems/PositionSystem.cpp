// Altered SFML Transformable.cpp for Ancona's positioning

////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2018 Laurent Gomila (laurent@sfml-dev.org)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#include <cmath>

#include <Ancona/Core2D/Systems/PositionSystem.hpp>

REGISTER_POLYMORPHIC_SERIALIZER(ild::PositionComponent);

namespace ild
{
std::ostream & operator<<(std::ostream & os, const Vector2f & pt)
{
    os << "(" << pt.x << "," << pt.y << ")";
    return os;
}

std::ostream & operator<<(std::ostream && os, const Vector2f & pt)
{
    os << "(" << pt.x << "," << pt.y << ")";
    return os;
}

void PositionComponent::Serialize(Archive & arc)
{
    Vector2f position;
    arc(position, "position");
    _transform.position(position);
    _interpolatedTransform.position(position);

    arc(_velocity, "velocity");
}

void PositionComponent::FetchDependencies(const Entity & entity)
{
}

void PositionComponent::PreUpdate()
{
    _previousPosition = _transform.position();
}

void PositionComponent::Update(float delta)
{
    if (_velocity.x != 0.0f || _velocity.y != 0.0f)
    {
        _transform.Move(delta * _velocity);
    }
}

/* getters and setters */

const Vector2f & PositionComponent::position() const
{
    return _transform.position();
}

void PositionComponent::position(const Vector2f & position)
{
    _transform.position(position);
}

const Transform & PositionComponent::transform() const
{
    return _transform;
}

const Vector2f PositionComponent::interpolatedPosition(float alpha) const
{
    return _previousPosition * (1.0f - alpha) + _transform.position() * alpha;
}

const Transform & PositionComponent::interpolatedTransform(float alpha)
{
    _interpolatedTransform.position(interpolatedPosition(alpha));
    return _interpolatedTransform;
}

PositionSystem::PositionSystem(std::string systemName, SystemManager & manager) :
        UnorderedSystem<PositionComponent>(systemName, manager, UpdateStep::Physics)
{
}

void PositionSystem::Update(float delta)
{
    for (EntityComponentPair pair : *this)
    {
        pair.second->Update(delta);
    }
}

void PositionSystem::PreUpdate()
{
    for (EntityComponentPair pair : *this)
    {
        pair.second->PreUpdate();
    }
}

PositionComponent * PositionSystem::CreateComponent(const Entity & entity)
{
    auto comp = new PositionComponent();
    AttachComponent(entity, comp);
    return comp;
}
} // namespace ild
