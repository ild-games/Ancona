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

#pragma once

#include <Ancona/Framework/EntityFramework/UnorderedSystem.hpp>
#include <Ancona/Framework/Serializing/Serializing.hpp>
#include <Ancona/Util/Vector2.hpp>

namespace ild
{

/**
 * @brief Operator used to output a Vector2f to an out stream. The Vector2f will be formatted as (x,y)
 */
std::ostream & operator<<(std::ostream & os, const Vector2f & pt);

class PositionComponent
{
  public:
    /**
     * @brief Overriable default destructor.
     */
    ~PositionComponent() {}

    /**
     * @copydoc ild::CameraComponent::Serialize
     */
    void Serialize(Archive & arc);

    /**
     * @copydoc ild::CameraComponent::FetchDependencies
     */
    void FetchDependencies(const Entity & entity);

    void PreUpdate();
    void Update(float delta);

    /* getters and setters */
    inline const Vector2f & velocity() const { return _velocity; }
    inline void velocity(const Vector2f & velocity) { _velocity = velocity; }

    const Vector2f position() const;
    void position(const Vector2f & position);
    const Transform & transform() const;
    const Vector2f & interpolatedPosition(float alpha) const;
    const Transform & interpolatedTransform(float alpha) const;

  protected:
    Transform _transform;
    Vector2f _origin = Vector2f(0, 0);
    Vector2f _scale = Vector2f(1, 1);
    float _rotation = 0;
    Vector2f _previousPosition = Vector2f(0, 0);
    Vector2f _velocity = Vector2f(0, 0);
};

/**
 * @brief A Base Position System that allows access
 *  to information that is not closely tied to a games world.
 * @author Jeff Swenson
 */
class PositionSystem : public UnorderedSystem<PositionComponent>
{
  public:
    /**
     * @brief Constructor of a PositionSystem and register it with the manager.
     *
     * @param systemName Name of the system.
     * @param manager Manager that the system belongs to.
     */
    PositionSystem(std::string systemName, SystemManager & manager);

    /**
     * Create a position component at (0,0)
     * @param Entity entity to create the component for.
     */
    PositionComponent * CreateComponent(const Entity & entity);

  protected:
    void PreUpdate() override;
    /**
     * @brief Update the position components.  Must be implemented by the child position system.
     *
     * @param delta Fraction of a second since the last update.
     */
    void Update(float delta) override;
};

} // namespace ild
