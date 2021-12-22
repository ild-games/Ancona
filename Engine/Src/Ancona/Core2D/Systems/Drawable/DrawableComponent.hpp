#pragma once

#include <memory>

#include <Ancona/Core2D/Systems/CameraSystem.hpp>
#include <Ancona/Core2D/Systems/Drawable/ContainerDrawable.hpp>
#include <Ancona/Core2D/Systems/PositionSystem.hpp>
#include <Ancona/HAL.hpp>

namespace ild
{

class DrawableSystem;

/**
 * @brief Component used to draw elements on an entity.
 *
 * @author Tucker Lein
 */
class DrawableComponent
{
  public:
    /**
     * @brief Default constructor, should only be used by the serializer.
     */
    DrawableComponent() {}

    /**
     * @brief Construct a DrawableComponent.
     *
     * @param topDrawable Drawable to associate the DrawableComponent with.
     * @param cameraComponent CameraComponent used to render these renderables.
     */
    DrawableComponent(
        std::unique_ptr<Drawable> topDrawable,
        DrawableSystem * drawableSystem,
        PositionSystem * positionSystem,
        CameraComponent * cameraComponent);

    DrawableComponent & operator=(DrawableComponent & rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }

        _topDrawable.reset(rhs.topDrawable()->Copy());
        _camera = rhs.cameraComponent();
        _cameraSystem = rhs.cameraSystem();
        _positionSystem = rhs.positionSystem();
        _positionComponent = rhs.positionComponent();
        _drawableSystem = rhs.drawableSystem();
        _camEntity = rhs.camEntity();
        return *this;
    }

    /**
     * @brief Gets the specified drawable that is on the component.
     *
     * @param key Key for the drawable element.
     */
    Drawable * GetDrawable(const std::string & key);

    /**
     * @brief Draws the DrawableComponent
     */
    void Draw(ildhal::RenderTarget & target, float delta);
    void PostDrawUpdate(float delta);

    /**
     * @copydoc ild::CameraComponent::FetchDependencies
     */
    void FetchDependencies(const Entity & entity);

    /**
     * Get the bounding box for the drawable. Used to determine if the drawable should be rendered.
     * @return Bounding box describing the edge of the drawable.
     */
    Box2 BoundingBox();

    /**
     * @copydoc ild::CameraComponent::Serialize
     */
    void Serialize(Archive & arc);

    /* getters and setters */
    Drawable * topDrawable() { return _topDrawable.get(); }
    CameraComponent * cameraComponent() { return _camera; }
    CameraSystem * cameraSystem() { return _cameraSystem; }
    PositionSystem * positionSystem() { return _positionSystem; }
    PositionComponent * positionComponent() { return _positionComponent; }
    DrawableSystem * drawableSystem() { return _drawableSystem; }
    const Entity & camEntity() { return _camEntity; }

  private:
    std::unique_ptr<Drawable> _topDrawable;
    CameraComponent * _camera;
    CameraSystem * _cameraSystem;
    PositionSystem * _positionSystem;
    PositionComponent * _positionComponent;
    DrawableSystem * _drawableSystem;
    Entity _camEntity = nullentity;
};

} // namespace ild
