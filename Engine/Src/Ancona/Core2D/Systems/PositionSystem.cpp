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
std::ostream &operator<<(std::ostream &os, const Vector2f &pt)
{
    os << "(" << pt.x << "," << pt.y << ")";
    return os;
}

std::ostream &operator<<(std::ostream &&os, const Vector2f &pt)
{
    os << "(" << pt.x << "," << pt.y << ")";
    return os;
}

void PositionComponent::Serialize(Archive &arc)
{
    arc(_actualPosition, "position");
    arc(_velocity, "velocity");
}

void PositionComponent::FetchDependencies(const Entity &entity)
{
    _transformNeedsUpdate = true;
}

void PositionComponent::PreUpdate()
{
    _previousPosition = _actualPosition;
}

void PositionComponent::Update(float delta)
{
    if (_velocity.x != 0.0f || _velocity.y != 0.0f)
    {
        _actualPosition += delta * _velocity;
    }
}

const Vector2f PositionComponent::RoundPosition(const Vector2f &position) const
{
    return Vector2f(std::round(position.x * 128) / 128, std::round(position.y * 128) / 128);
}

/* getters and setters */

const Vector2f PositionComponent::position() const
{
    return _actualPosition;
}

const Vector2f PositionComponent::interpolatedPosition(float alpha) const
{
    return _previousPosition * (1.0f - alpha) + _actualPosition * alpha;
}

void PositionComponent::position(const Vector2f &position)
{
    _actualPosition = position;

    _transformNeedsUpdate = true;
}

const Transform &PositionComponent::transform() const
{
    // Recompute the combined transform if needed
    if (_transformNeedsUpdate)
    {
        float angle = -_rotation * 3.141592654f / 180.f;
        float cosine = static_cast<float>(std::cos(angle));
        float sine = static_cast<float>(std::sin(angle));
        float sxc = _scale.x * cosine;
        float syc = _scale.y * cosine;
        float sxs = _scale.x * sine;
        float sys = _scale.y * sine;
        float tx = -_origin.x * sxc - _origin.y * sys + _actualPosition.x;
        float ty = _origin.x * sxs - _origin.y * syc + _actualPosition.y;

        _transform = Transform(sxc, sys, tx, -sxs, syc, ty, 0.f, 0.f, 1.f);
        _transformNeedsUpdate = false;
    }

    return _transform;
}

Transform PositionComponent::interpolatedTransform(float alpha) const
{
    const Vector2f position = interpolatedPosition(alpha);

    float angle = -_rotation * 3.141592654f / 180.f;
    float cosine = static_cast<float>(std::cos(angle));
    float sine = static_cast<float>(std::sin(angle));
    float sxc = _scale.x * cosine;
    float syc = _scale.y * cosine;
    float sxs = _scale.x * sine;
    float sys = _scale.y * sine;
    float tx = -_origin.x * sxc - _origin.y * sys + position.x;
    float ty = _origin.x * sxs - _origin.y * syc + position.y;

    return Transform(sxc, sys, tx, -sxs, syc, ty, 0.f, 0.f, 1.f);
}

PositionSystem::PositionSystem(std::string systemName, SystemManager &manager)
    : UnorderedSystem<PositionComponent>(systemName, manager, UpdateStep::Physics)
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

PositionComponent *PositionSystem::CreateComponent(const Entity &entity)
{
    auto comp = new PositionComponent();
    AttachComponent(entity, comp);
    return comp;
}
} // namespace ild
